using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using WixToolset.Bootstrapper;

namespace InstallerUI.Bootstrapper
{
   public class BootstrapperApp : BootstrapperApplication
   {
      public BootstrapperApp()
      {
         _window = null;
      }

      protected override void Run()
      {
         _oneInstance = new Mutex(true, "MARE_Installer_Mutex", out _isRunning);
         if(_isRunning && _oneInstance.WaitOne())
         {
            _window = new InstallerWindow(this);
            _window.ShowDialog();
            _oneInstance.ReleaseMutex();
         }
         else
         {
            MessageBox.Show("Only one instance of the installer can run simultaneously.", "MARE", MessageBoxButton.OK, MessageBoxImage.Error);
         }

         this.Engine.Quit(0);
      }

      protected override void OnShutdown(ShutdownEventArgs args)
      {
         _isRunning = false;
         _oneInstance.Close();

         if(_window != null)
         {
            _window.Close();
         }

         base.OnShutdown(args);
      }

      private InstallerWindow _window;
      bool _isRunning;
      Mutex _oneInstance;
   }
}
