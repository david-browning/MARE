using System;
using System.Windows;
using System.Windows.Controls;
using InstallerUI.Bootstrapper;
using WixToolset.Bootstrapper;

namespace InstallerUI.UI
{
   public class UIModel : BootstrapperModel
   {
      public UIModel(Window programWindow,
         Frame navFrame,
         BootstrapperApplication bootstrapper) :
         base(bootstrapper, programWindow)
      {
         _navFrame = navFrame;
         IsBootstrapperWorking = true;
         MBHandler = new Controls.MessageBoxHandler(programWindow);

         _bootstrapper.DetectBegin += this.Bootstrapper_DetectBegin;
         _bootstrapper.DetectComplete += this._bootstrapper_DetectComplete;

         _bootstrapper.PlanComplete += this.Bootstrapper_PlanComplete;
         _bootstrapper.PlanBegin += this.Bootstrapper_PlanBegin;

         _bootstrapper.ExecutePackageBegin += this.Bootstrapper_ExecutePackageBegin;

         _bootstrapper.ApplyBegin += this.Bootstrapper_ApplyBegin;
         _bootstrapper.ApplyComplete += this.Bootstrapper_ApplyComplete;
      }

      protected override void OnError(ErrorArgs e)
      {
         LastError = e;
         IsBootstrapperWorking = false;
         base.OnError(e);
      }

      public void Navigate(CommonPage p)
      {
         _navFrame.Navigate(p);
      }

      public void NavigateBack()
      {
         _navFrame.GoBack();
      }

      private void Bootstrapper_DetectBegin(object sender, DetectBeginEventArgs e)
      {
         CurrentAction = DETECT_BEGIN_MESSAGE;
         IsBootstrapperWorking = true;
      }

      private void _bootstrapper_DetectComplete(object sender, DetectCompleteEventArgs e)
      {
         CurrentAction = DETECT_COMPLETE_MESSAGE;
         IsBootstrapperWorking = false;
      }

      private void Bootstrapper_PlanBegin(object sender, PlanBeginEventArgs e)
      {
         CurrentAction = PLAN_BEGIN_MESSAGE;
         IsBootstrapperWorking = true;
      }

      private void Bootstrapper_PlanComplete(object sender, PlanCompleteEventArgs e)
      {
         CurrentAction = PLAN_COMPLETE_MESSAGE;
         IsBootstrapperWorking = false;
      }

      private void Bootstrapper_ExecutePackageBegin(object sender, ExecutePackageBeginEventArgs e)
      {
         CurrentInstall = e.PackageId;
      }
      
      private void Bootstrapper_ApplyBegin(object sender, ApplyBeginEventArgs e)
      {
         this.Progress = 0;
      }

      private void Bootstrapper_ApplyComplete(object sender, ApplyCompleteEventArgs e)
      {
         this.Progress = 0;
      }

      #region UI Fields
      public string CurrentInstall
      {
         get { return _currentInstall; }
         set
         {
            _currentInstall = value;
            OnPropertyChanged();
         }
      }

      public string CurrentAction
      {
         get { return _currentAction; }
         set
         {
            _currentAction = value;
            OnPropertyChanged();
         }
      }

      public bool IsBootstrapperWorking
      {
         get { return _isBootstrapperWorking; }
         set
         {
            _isBootstrapperWorking = value;
            OnPropertyChanged();
         }
      }

      public string ProductMethod
      {
         get
         {
            switch(base.InstallerActionState)
            {
               case LaunchAction.Install:
               {
                  return "Install";
               }
               case LaunchAction.Modify:
               {
                  return "Modify";
               }
               case LaunchAction.Repair:
               {
                  return "Repair";
               }
               case LaunchAction.Uninstall:
               {
                  return "Remove";
               }
               default:
               {
                  throw new MemberAccessException();
               }
            }
         }
      }

      public string ProductMethodIng
      {
         get { return ProductMethod + "ing"; }
      }

      public string ProductMethodEd
      {
         get { return ProductMethod + "ed"; }
      }

      public string FeaturePageTitle
      {
         get
         {
            string action;
            if(base.InstallerActionState == LaunchAction.Install)
            {
               action = "install";
            }
            else if(base.InstallerActionState == LaunchAction.Modify)
            {
               action = "keep";
            }
            else
            {
               throw new Exception();
            }

            return "Select features to " + action;
         }
      }

      public string ActionCompleteTitle
      {
         get
         {
            return "MARE is " + ProductMethodEd;
         }
      }

      public string CancelTitle
      {
         get
         {
            return string.Format("Are you sure you want to stop {0}?", ProductMethodIng);
         }
      }

      public string ErrorMessage
      {
         get
         {
            return string.Format("There was a problem during {0}: {1} The error code was {2}. HRESULT was {3}",
               LastError.Message, LastError.Message, LastError.ErrorCode, LastError.HResult);
         }
      }

      public string ErrorTitle
      {
         get
         {
            return string.Format("There was a problem while {0}.", ProductMethodIng);
         }
      }
      #endregion

      public Controls.MessageBoxHandler MBHandler { get; protected set; }

      private Frame _navFrame { get; set; }

      private string _currentInstall = "";
      private string _currentAction = "Processing";
      private bool _isBootstrapperWorking = false;

      const string DETECT_BEGIN_MESSAGE = "Detecting Packages";
      const string DETECT_COMPLETE_MESSAGE = "Done Detecting";
      const string PLAN_BEGIN_MESSAGE = "Planning Installation";
      const string PLAN_COMPLETE_MESSAGE = "Done Planning";
   }
}
