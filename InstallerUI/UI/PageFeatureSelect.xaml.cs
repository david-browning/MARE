using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using InstallerUI.InstallerComponents;
using InstallerUI.UI;

namespace InstallerUI.Pages
{
   /// <summary>
   /// Interaction logic for PageFeatureSelect.xaml
   /// </summary>
   public partial class PageFeatureSelect : CommonPage
   {
      public PageFeatureSelect(UIModel m) :
          base(m)
      {
         InitializeComponent();
         //_installImage.Source = System.Windows.Interop.Imaging.CreateBitmapSourceFromHIcon(
         //   System.Drawing.SystemIcons.Shield.Handle, Int32Rect.Empty, BitmapSizeOptions.FromEmptyOptions());
         NativeMethods.SHSTOCKICONINFO iconResult = new NativeMethods.SHSTOCKICONINFO();
         iconResult.cbSize = (uint)System.Runtime.InteropServices.Marshal.SizeOf(iconResult);

         NativeMethods.SHGetStockIconInfo(
             NativeMethods.SHSTOCKICONID.SIID_SHIELD,
             NativeMethods.SHGSI.SHGSI_ICON | NativeMethods.SHGSI.SHGSI_SMALLICON,
             ref iconResult);

         _installImage.Source = System.Windows.Interop.Imaging.CreateBitmapSourceFromHIcon(
            iconResult.hIcon, Int32Rect.Empty, BitmapSizeOptions.FromEmptyOptions());

         m._bootstrapper.PlanComplete += this._bootstrapper_PlanComplete;
      }

      private void _bootstrapper_PlanComplete(object sender, WixToolset.Bootstrapper.PlanCompleteEventArgs e)
      {
         Dispatcher.BeginInvoke(System.Windows.Threading.DispatcherPriority.Loaded, (ThreadStart)delegate ()
         {
            UIModel._bootstrapper.PlanComplete -= this._bootstrapper_PlanComplete;
            this.UIModel.Navigate(new PageProgress(UIModel));
         });
      }

      private static class NativeMethods
      {
         [DllImport("Shell32.dll", SetLastError = false)]
         public static extern Int32 SHGetStockIconInfo(SHSTOCKICONID siid, SHGSI uFlags, ref SHSTOCKICONINFO psii);

         public enum SHSTOCKICONID : uint
         {
            SIID_DOCNOASSOC = 0,
            SIID_DOCASSOC = 1,
            SIID_APPLICATION = 2,
            SIID_FOLDER = 3,
            SIID_FOLDEROPEN = 4,
            SIID_DRIVE525 = 5,
            SIID_DRIVE35 = 6,
            SIID_DRIVEREMOVE = 7,
            SIID_DRIVEFIXED = 8,
            SIID_DRIVENET = 9,
            SIID_DRIVENETDISABLED = 10,
            SIID_DRIVECD = 11,
            SIID_DRIVERAM = 12,
            SIID_WORLD = 13,
            SIID_SERVER = 15,
            SIID_PRINTER = 16,
            SIID_MYNETWORK = 17,
            SIID_FIND = 22,
            SIID_HELP = 23,
            SIID_SHARE = 28,
            SIID_LINK = 29,
            SIID_SLOWFILE = 30,
            SIID_RECYCLER = 31,
            SIID_RECYCLERFULL = 32,
            SIID_MEDIACDAUDIO = 40,
            SIID_LOCK = 47,
            SIID_AUTOLIST = 49,
            SIID_PRINTERNET = 50,
            SIID_SERVERSHARE = 51,
            SIID_PRINTERFAX = 52,
            SIID_PRINTERFAXNET = 53,
            SIID_PRINTERFILE = 54,
            SIID_STACK = 55,
            SIID_MEDIASVCD = 56,
            SIID_STUFFEDFOLDER = 57,
            SIID_DRIVEUNKNOWN = 58,
            SIID_DRIVEDVD = 59,
            SIID_MEDIADVD = 60,
            SIID_MEDIADVDRAM = 61,
            SIID_MEDIADVDRW = 62,
            SIID_MEDIADVDR = 63,
            SIID_MEDIADVDROM = 64,
            SIID_MEDIACDAUDIOPLUS = 65,
            SIID_MEDIACDRW = 66,
            SIID_MEDIACDR = 67,
            SIID_MEDIACDBURN = 68,
            SIID_MEDIABLANKCD = 69,
            SIID_MEDIACDROM = 70,
            SIID_AUDIOFILES = 71,
            SIID_IMAGEFILES = 72,
            SIID_VIDEOFILES = 73,
            SIID_MIXEDFILES = 74,
            SIID_FOLDERBACK = 75,
            SIID_FOLDERFRONT = 76,
            SIID_SHIELD = 77,
            SIID_WARNING = 78,
            SIID_INFO = 79,
            SIID_ERROR = 80,
            SIID_KEY = 81,
            SIID_SOFTWARE = 82,
            SIID_RENAME = 83,
            SIID_DELETE = 84,
            SIID_MEDIAAUDIODVD = 85,
            SIID_MEDIAMOVIEDVD = 86,
            SIID_MEDIAENHANCEDCD = 87,
            SIID_MEDIAENHANCEDDVD = 88,
            SIID_MEDIAHDDVD = 89,
            SIID_MEDIABLURAY = 90,
            SIID_MEDIAVCD = 91,
            SIID_MEDIADVDPLUSR = 92,
            SIID_MEDIADVDPLUSRW = 93,
            SIID_DESKTOPPC = 94,
            SIID_MOBILEPC = 95,
            SIID_USERS = 96,
            SIID_MEDIASMARTMEDIA = 97,
            SIID_MEDIACOMPACTFLASH = 98,
            SIID_DEVICECELLPHONE = 99,
            SIID_DEVICECAMERA = 100,
            SIID_DEVICEVIDEOCAMERA = 101,
            SIID_DEVICEAUDIOPLAYER = 102,
            SIID_NETWORKCONNECT = 103,
            SIID_INTERNET = 104,
            SIID_ZIPFILE = 105,
            SIID_SETTINGS = 106,
            SIID_DRIVEHDDVD = 132,
            SIID_DRIVEBD = 133,
            SIID_MEDIAHDDVDROM = 134,
            SIID_MEDIAHDDVDR = 135,
            SIID_MEDIAHDDVDRAM = 136,
            SIID_MEDIABDROM = 137,
            SIID_MEDIABDR = 138,
            SIID_MEDIABDRE = 139,
            SIID_CLUSTEREDDRIVE = 140,
            SIID_MAX_ICONS = 175

         }

         [Flags]
         public enum SHGSI : uint
         {
            SHGSI_ICON = 0x000000100,
            SHGSI_SMALLICON = 0x000000001
         }

         [StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
         public struct SHSTOCKICONINFO
         {
            public UInt32 cbSize;
            public IntPtr hIcon;
            public Int32 iSysIconIndex;
            public Int32 iIcon;

            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 260)]
            public string szPath;
         }
      }

      private void _backButton_Click(object sender, RoutedEventArgs e)
      {
         UIModel.NavigateBack();
      }

      private void _installButton_Click(object sender, RoutedEventArgs e)
      {
            UIModel.Plan();
      }

      private void CommonPage_Loaded(object sender, RoutedEventArgs e)
      {
        
      }
   }
}
