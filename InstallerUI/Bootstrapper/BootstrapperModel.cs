using System;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Threading;
using System.Windows;
using System.Windows.Interop;
using InstallerUI.InstallerComponents;
using WixToolset.Bootstrapper;

namespace InstallerUI.Bootstrapper
{
   public class BootstrapperModel : INotifyPropertyChanged
   {
      public BootstrapperModel(BootstrapperApplication bootstrapper,
         Window window)
      {
         _bootstrapper = bootstrapper;
         _windowHandle = new WindowInteropHelper(window).Handle;
         _manifest = new ManifestParser(_bootstrapper.BAManifest.BADataFile);
         InstallerFeatures = new ObservableCollection<InstallableFeature>();
         InstallerPackages = new ObservableCollection<InstallablePackage>();
         this.InstallerActionState = LaunchAction.Install;
         _wait = new ManualResetEvent(true);
         _wait.Set();
         SetupEvents();
      }

      public void Detect()
      {
         _bootstrapper.Engine.Detect(_windowHandle);
      }

      public void Plan()
      {
         _bootstrapper.Engine.Plan(this.InstallerActionState);
      }

      public void Apply()
      {
         _bootstrapper.Engine.Apply(_windowHandle);
      }

      public void Pause()
      {
         _wait.Reset();
         Paused();
      }

      public void Resume()
      {
         _wait.Set();
         Resumed();
      }

      public void Quit(int code)
      {
         _bootstrapper.Engine.Quit(code);
      }

      public void Cancel(int code)
      {
         Quit(code);
      }

      protected virtual void OnError(ErrorArgs e)
      {
         MessageBox.Show("Internal Error");
         LastError = e;
         OnErrorEvent(e);
      }

      private void SetupEvents()
      {
         _bootstrapper.DetectBegin += this._bootstrapper_DetectBegin;
         _bootstrapper.DetectComplete += this._bootstrapper_DetectComplete;
         _bootstrapper.DetectMsiFeature += this._bootstrapper_DetectMsiFeature;
         _bootstrapper.DetectPackageComplete += this._bootstrapper_DetectPackageComplete;

         _bootstrapper.PlanComplete += this._bootstrapper_PlanComplete;
         _bootstrapper.PlanPackageBegin += this._bootstrapper_PlanPackageBegin;
         _bootstrapper.PlanMsiFeature += this._bootstrapper_PlanMsiFeature;

         _bootstrapper.ElevateComplete += this._bootstrapper_ElevateComplete;
         _bootstrapper.ExecuteProgress += this._bootstrapper_ExecuteProgress;
      }

      private void _bootstrapper_ExecuteProgress(object sender, ExecuteProgressEventArgs e)
      {
         this.Progress = e.OverallPercentage;
         _wait.WaitOne();
      }

      private void _bootstrapper_ElevateComplete(object sender, ElevateCompleteEventArgs e)
      {
         if(e.Status != 0)
         {
            OnError(new ErrorArgs(BOOTSTRAPPER_APPLICATION_MESSAGE.OnElevateComplete, e.Status, e.HResult));
         }
      }

      private void _bootstrapper_PlanComplete(object sender, PlanCompleteEventArgs e)
      {
         if(e.Status != 0)
         {
            OnError(new ErrorArgs(BOOTSTRAPPER_APPLICATION_MESSAGE.OnPlanComplete,
               e.Status, e.HResult));
            return;
         }
      }

      private void _bootstrapper_PlanPackageBegin(object sender, PlanPackageBeginEventArgs e)
      {
         var package = InstallerPackages.Single(p => p.ID == e.PackageId);
         if(package == null)
         {
            OnError(new ErrorArgs(BOOTSTRAPPER_APPLICATION_MESSAGE.OnPlanPackageBegin,
                   ERROR_CANNOT_FIND_PACKAGE, 0, e.PackageId, null));
            e.Cancel = true;
            return;
         }

         //If the package is not a dependency: IE .NET or VC Runtime
         //And the action is not install and the package is installed
         if(InstallerActionState != LaunchAction.Install && package.IsDependency &&
            package.IsInstalled)
         {
            e.State = RequestState.None;
         }
         else
         {
            e.State = e.RecommendedState;
         }
      }

      private void _bootstrapper_PlanMsiFeature(object sender, PlanMsiFeatureEventArgs e)
      {
         var feature = InstallerFeatures.Single(f => f.ID == e.FeatureId);
         if(feature == null)
         {
            OnError(new ErrorArgs(BOOTSTRAPPER_APPLICATION_MESSAGE.OnPlanMsiFeature,
               ERROR_CANNOT_FIND_FEATURE, 0, null, e.FeatureId));
            e.Cancel = true;
            return;
         }

         //Update the feature state to either include or not.
         if(InstallerActionState == LaunchAction.Install ||
            InstallerActionState == LaunchAction.Modify ||
            InstallerActionState == LaunchAction.Repair)
         {
            //If installing, repairing, or modifying, check means include.
            e.State = feature.IsChecked == true ? FeatureState.Local : FeatureState.Absent;
         }
         else if(InstallerActionState == LaunchAction.Uninstall)
         {
            //Uninstalling, force the state to absent.
            e.State = FeatureState.Absent;
         }
         else
         {
            OnError(new ErrorArgs(BOOTSTRAPPER_APPLICATION_MESSAGE.OnPlanMsiFeature,
            ERROR_UNKNOWN_STATE, 0, null, e.FeatureId));
            e.Cancel = true;
            return;
         }
      }

      private void _bootstrapper_DetectBegin(object sender, DetectBeginEventArgs e)
      {
         IsProductInstalled = e.Installed;
      }

      private void _bootstrapper_DetectComplete(object sender, DetectCompleteEventArgs e)
      {
         if(e.Status != 0)
         {
            OnError(new ErrorArgs(BOOTSTRAPPER_APPLICATION_MESSAGE.OnDetectComplete,
               e.Status, e.HResult));
            return;
         }
      }

      private void _bootstrapper_DetectMsiFeature(object sender, DetectMsiFeatureEventArgs e)
      {
         var xmlPackage = _manifest.LookupFeatureXML(e.FeatureId);
         if(xmlPackage == null)
         {
            OnError(new ErrorArgs(BOOTSTRAPPER_APPLICATION_MESSAGE.OnDetectMsiFeature,
               ERROR_CANNOT_FIND_PACKAGE, 0, null, e.FeatureId));
            e.Cancel = true;
            return;
         }

         bool shouldInstallFeature = true;
         if(InstallerActionState == LaunchAction.Uninstall ||
            InstallerActionState == LaunchAction.Modify)
         {
            shouldInstallFeature = e.State == FeatureState.Absent ? false : true;
         }

         InstallerFeatures.Add(new InstallableFeature()
         {
            Name = _manifest.LookupFeatureName(xmlPackage),
            Description = _manifest.LookupFeatureDescription(xmlPackage),
            ID = e.FeatureId,
            Attributes = _manifest.LookupFeatureAttributes(xmlPackage),
            IsInstalled = shouldInstallFeature,
            IsChecked = shouldInstallFeature,
         });
      }

      private void _bootstrapper_DetectPackageComplete(object sender, DetectPackageCompleteEventArgs e)
      {
         var xmlPackage = _manifest.LookupPackageXML(e.PackageId);
         if(xmlPackage == null)
         {
            OnError(new ErrorArgs(BOOTSTRAPPER_APPLICATION_MESSAGE.OnDetectPackageComplete,
            ERROR_CANNOT_FIND_PACKAGE, 0, e.PackageId, null));
            return;
         }

         bool isPackageInstalled = e.State == PackageState.Absent ? false : true;
         this.InstallerPackages.Add(new InstallablePackage()
         {
            Name = _manifest.LookupPackageName(xmlPackage),
            Description = _manifest.LookupPackageDescription(xmlPackage),
            ID = e.PackageId,
            IsInstalled = isPackageInstalled,
            IsDependency = _manifest.LookupPackageIsDependency(xmlPackage)
         });
      }

      public event PropertyChangedEventHandler PropertyChanged;
      protected void OnPropertyChanged([CallerMemberName] String propertyName = "")
      {
         if(PropertyChanged != null)
         {
            PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
         }
      }

      public bool IsProductInstalled
      {
         get { return _isProductInstalled; }
         protected set
         {
            _isProductInstalled = value;
            OnPropertyChanged();
         }
      }

      public ObservableCollection<InstallableFeature> InstallerFeatures
      {
         get { return _installerFeatures; }
         set
         {
            _installerFeatures = value;
            OnPropertyChanged();
         }
      }

      public ObservableCollection<InstallablePackage> InstallerPackages
      {
         get { return _installerPackages; }
         set
         {
            _installerPackages = value;
            OnPropertyChanged();
         }
      }

      public LaunchAction InstallerActionState
      {
         get { return _installerAction; }
         set
         {
            _installerAction = value;
            OnPropertyChanged();
         }
      }

      public int Progress
      {
         get { return _progress; }
         set
         {
            _progress = value;
            OnPropertyChanged();
         }
      }

      public ErrorArgs LastError
      {
         get { return _lastError; }
         set
         {
            _lastError = value;
            OnPropertyChanged();
         }
      }

      public BootstrapperApplication _bootstrapper { get; set; }
      private bool _isProductInstalled = false;
      private WixToolset.Bootstrapper.LaunchAction _installerAction = LaunchAction.Install;
      private ObservableCollection<InstallableFeature> _installerFeatures;
      private ObservableCollection<InstallablePackage> _installerPackages;
      private int _progress = 0;
      private ErrorArgs _lastError;
      private IntPtr _windowHandle;
      private ManifestParser _manifest;
      private ManualResetEvent _wait;

      public delegate void OnErrorHandler(ErrorArgs e);
      public event OnErrorHandler OnErrorEvent;

      public delegate void OnPauseHandler();
      public event OnPauseHandler Paused;

      public delegate void OnResumeHandler();
      public event OnResumeHandler Resumed;

      public const int ERROR_CODE_DETECT_FAILED = 1;
      public const int ERROR_CODE_PLAN_FAILED = 2;
      public const int ERROR_NULL_BUNDLE = 3;
      public const int ERROR_CANNOT_FIND_FEATURE = 4;
      public const int ERROR_CANNOT_FIND_PACKAGE = 5;
      public const int ERROR_UNKNOWN_STATE = 6;
   }

   public class ErrorArgs
   {
      public ErrorArgs(BOOTSTRAPPER_APPLICATION_MESSAGE message,
         int errorCode, int hresult = 0,
         string packageId = null, string featureId = null)
      {
         this.HResult = hresult;
         this.ErrorCode = errorCode;
         this.Message = message;
         this.PackageID = packageId;
         this.FeatureID = featureId;
      }

      public WixToolset.Bootstrapper.BOOTSTRAPPER_APPLICATION_MESSAGE Message { get; private set; }
      public int ErrorCode { get; private set; }

      public int HResult { get; private set; }
      public string PackageID { get; private set; }
      public string FeatureID { get; private set; }
   }

}
