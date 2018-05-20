using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using InstallerUI.UI;

namespace InstallerUI.Pages
{
   public partial class PageMain : CommonPage
   {
      public PageMain(UIModel m) :
          base(m)
      {
         InitializeComponent();
      }

      private void _installButton_Click(object sender, RoutedEventArgs e)
      {
         UIModel.InstallerActionState = WixToolset.Bootstrapper.LaunchAction.Install;
         Dispatcher.BeginInvoke(System.Windows.Threading.DispatcherPriority.Loaded, (ThreadStart)delegate ()
         {
            UIModel.Navigate(new PageFeatureSelect(UIModel));
         });
      }

      private void _modifyButton_Click(object sender, RoutedEventArgs e)
      {
         UIModel.InstallerActionState = WixToolset.Bootstrapper.LaunchAction.Modify;
         Dispatcher.BeginInvoke(System.Windows.Threading.DispatcherPriority.Loaded, (ThreadStart)delegate ()
         {
            UIModel.Navigate(new PageFeatureSelect(UIModel));
         });
      }

      private void _repairButton_Click(object sender, RoutedEventArgs e)
      {
         UIModel.InstallerActionState = WixToolset.Bootstrapper.LaunchAction.Repair;
         UIModel._bootstrapper.PlanComplete += this._bootstrapper_PlanComplete;
         UIModel.Plan();
      }

      private void _removeButton_Click(object sender, RoutedEventArgs e)
      {
         UIModel.InstallerActionState = WixToolset.Bootstrapper.LaunchAction.Uninstall;
         UIModel._bootstrapper.PlanComplete += this._bootstrapper_PlanComplete;
         UIModel.Plan();
      }

      private void _bootstrapper_PlanComplete(object sender, WixToolset.Bootstrapper.PlanCompleteEventArgs e)
      {
         Dispatcher.BeginInvoke(System.Windows.Threading.DispatcherPriority.Loaded, (ThreadStart)delegate ()
         {
            UIModel.Navigate(new PageProgress(UIModel));
         });
      }

      private void CommonPage_Loaded(object sender, RoutedEventArgs e)
      {
      }
   }
}
