using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace InstallerUI.Controls
{
   public class MessageBoxHandler
   {
      public MessageBoxHandler(Window window)
      {
         _window = window;
      }

      public void MBCannotDetectPackages()
      {
         ErrorMessageBox(string.Format("The installer could not detect packages.\n{0}", MessageBoxMessages.PROG_MUST_EXIT_MESSAGE), 
            MessageBoxTitles.INSTALL_ERROR_TITLE, MessageBoxButton.OK);
      }

      public void MBCannotPlan()
      {
         ErrorMessageBox(string.Format("The installer could not plan packages.\n{0}", MessageBoxMessages.PROG_MUST_EXIT_MESSAGE),
            MessageBoxTitles.PLAN_ERROR_TITLE, MessageBoxButton.OK);
      }

      public void MBUnknownState(WixToolset.Bootstrapper.LaunchAction action)
      {
         ErrorMessageBox(string.Format("The installer is in an unknown state and cannot continue.\nThe state is {0}", action), 
            MessageBoxTitles.INSTALL_ERROR_TITLE, MessageBoxButton.OK);
      }

      public void MBCannotLookupPackage(string packageId)
      {
         ErrorMessageBox(string.Format("Could not look up the package with ID {0}.\n{1}", 
            packageId, MessageBoxMessages.PROG_MUST_EXIT_MESSAGE), 
            MessageBoxTitles.LOOKUP_ERROR_TITLE, 
            MessageBoxButton.OK);
      }

      public void MBCannotLookupFeature(string featureId)
      {
         ErrorMessageBox(string.Format("Could not look up the feature with ID {0}.\n{1}",
            featureId, MessageBoxMessages.PROG_MUST_EXIT_MESSAGE),
            MessageBoxTitles.LOOKUP_ERROR_TITLE,
            MessageBoxButton.OK);
      }

      public MessageBoxResult ErrorMessageBox(string message, string title, MessageBoxButton button)
      {
         return MessageBox.Show(_window, message, title, button, MessageBoxImage.Error);
      }

      private Window _window;

      protected static class MessageBoxTitles
      {
         public const string INSTALL_ERROR_TITLE = "Install Error";
         public const string PLAN_ERROR_TITLE = "Planning Error";
         public const string LOOKUP_ERROR_TITLE = "Lookup Error";


      }

      protected static class MessageBoxMessages
      {
         public const string PROG_MUST_EXIT_MESSAGE = "The program must exit.";
      }
   }
}
