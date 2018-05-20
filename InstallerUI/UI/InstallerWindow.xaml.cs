using System;
using System.Threading;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Navigation;
using InstallerUI.Bootstrapper;
using InstallerUI.Pages;
using InstallerUI.UI;
using WixToolset.Bootstrapper;

namespace InstallerUI
{
   public partial class InstallerWindow : Window
   {
      public InstallerWindow(BootstrapperApplication b)
      {
         InitializeComponent();
         _allowDirectNavigation = true;
         UIModel = new UIModel(this, _navFrame, b);
         UIModel._bootstrapper.DetectComplete += this._bootstrapper_DetectComplete;
         UIModel.OnErrorEvent += this.UIModel_OnErrorEvent;
         UIModel._bootstrapper.ApplyComplete += this._bootstrapper_ApplyComplete;
         UIModel.Paused += this.UIModel_Paused;
         UIModel.Resumed += this.UIModel_Resumed;
         UIModel.Detect();
      }

      private void UIModel_Resumed()
      {
         MessageBox.Show("Resume");
      }

      private void UIModel_Paused()
      {
         MessageBox.Show("Pause");
         Dispatcher.BeginInvoke(System.Windows.Threading.DispatcherPriority.Loaded, (ThreadStart)delegate ()
         {
            UIModel.Navigate(new PageCancel(UIModel));
         });
      }

      private void _bootstrapper_ApplyComplete(object sender, ApplyCompleteEventArgs e)
      {
         Dispatcher.BeginInvoke(System.Windows.Threading.DispatcherPriority.Loaded, (ThreadStart)delegate ()
         {
            UIModel._bootstrapper.ApplyComplete -= this._bootstrapper_ApplyComplete;
            if(e.Status == 0)
            {
               UIModel.Navigate(new PageComplete(UIModel));
            }
         });
      }

      private void UIModel_OnErrorEvent(ErrorArgs e)
      {
         Dispatcher.BeginInvoke(System.Windows.Threading.DispatcherPriority.Loaded, (ThreadStart)delegate ()
         {
            UIModel.Cancel(e.ErrorCode);
            UIModel.Navigate(new PageError(UIModel));
         });
      }

      private void _bootstrapper_DetectComplete(object sender, DetectCompleteEventArgs e)
      {
         Dispatcher.BeginInvoke(System.Windows.Threading.DispatcherPriority.Loaded, (ThreadStart)delegate ()
         {
            UIModel.Navigate(new PageMain(UIModel));
         });
      }

      private void _window_Loaded(object sender, RoutedEventArgs e)
      {
      }

      private void _window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
      {
         e.Cancel = true;
         Dispatcher.BeginInvoke(System.Windows.Threading.DispatcherPriority.Loaded, (ThreadStart)delegate ()
         {
            UIModel.Navigate(new PageCancel(UIModel));
         });
      }

      private ThreadStart GetMoveLeftThread()
      {
         return (ThreadStart)delegate ()
         {
            var left = 0;
            var width = _navFrame.ActualWidth;
            DoubleAnimation animx = new DoubleAnimation(width, left, _duration);
            ;
            animx.EasingFunction = _transitionEasingFunction;
            TranslateTransform t = new TranslateTransform();
            _navFrame.RenderTransform = t;
            t.BeginAnimation(TranslateTransform.XProperty, animx);
         };
      }

      private ThreadStart GetMoveRightThread()
      {
         return (ThreadStart)delegate ()
         {
            var left = 0;
            var width = -_navFrame.ActualWidth;
            DoubleAnimation animx = new DoubleAnimation(width, left, _duration);
            ;
            animx.EasingFunction = _transitionEasingFunction;
            TranslateTransform t = new TranslateTransform();
            _navFrame.RenderTransform = t;
            t.BeginAnimation(TranslateTransform.XProperty, animx);
         };
      }

      private DoubleAnimation GetMoveLeftAnimation()
      {
         var left = 0;
         var width = -_navFrame.ActualWidth;
         DoubleAnimation animx = new DoubleAnimation(left, width, _duration);
         ;
         animx.Completed += Animx_Completed;
         animx.EasingFunction = _transitionEasingFunction;
         return animx;
      }

      private DoubleAnimation GetMoveRightAnimation()
      {
         var left = 0;
         var width = _navFrame.ActualWidth;
         DoubleAnimation animx = new DoubleAnimation(left, width, _duration);
         ;
         animx.Completed += Animx_Completed;
         animx.EasingFunction = _transitionEasingFunction;
         return animx;
      }

      private void _navFrame_Navigating(object sender, System.Windows.Navigation.NavigatingCancelEventArgs e)
      {
         if(Content != null && !_allowDirectNavigation)
         {
            e.Cancel = true;
            _navArgs = e;

            if(_navArgs.NavigationMode == NavigationMode.Back)
            {
               TranslateTransform t = new TranslateTransform();
               _navFrame.RenderTransform = t;
               t.BeginAnimation(TranslateTransform.XProperty, GetMoveRightAnimation());
            }
            else
            {
               TranslateTransform t = new TranslateTransform();
               _navFrame.RenderTransform = t;
               t.BeginAnimation(TranslateTransform.XProperty, GetMoveLeftAnimation());
            }

         }
         _allowDirectNavigation = false;
      }

      private void Animx_Completed(object sender, EventArgs e)
      {
         _allowDirectNavigation = true;
         switch(_navArgs.NavigationMode)
         {
            case NavigationMode.New:
            {
               if(_navArgs.Uri == null)
               {
                  _navFrame.Navigate(_navArgs.Content);
               }
               else
               {
                  _navFrame.Navigate(_navArgs.Uri);
               }

               Dispatcher.BeginInvoke(System.Windows.Threading.DispatcherPriority.Loaded, GetMoveLeftThread());

               break;
            }
            case NavigationMode.Back:
            {
               _navFrame.GoBack();
               Dispatcher.BeginInvoke(System.Windows.Threading.DispatcherPriority.Loaded, GetMoveRightThread());
               break;
            }
            case NavigationMode.Forward:
            {
               _navFrame.GoForward();
               Dispatcher.BeginInvoke(System.Windows.Threading.DispatcherPriority.Loaded, GetMoveLeftThread());
               break;
            }
            case NavigationMode.Refresh:
            {
               _navFrame.Refresh();
               Dispatcher.BeginInvoke(System.Windows.Threading.DispatcherPriority.Loaded, GetMoveRightThread());
               break;
            }
         }
      }

      private bool _allowDirectNavigation = false;
      private NavigatingCancelEventArgs _navArgs = null;
      private readonly Duration _duration = new Duration(TimeSpan.FromSeconds(0.15));
      private readonly IEasingFunction _transitionEasingFunction = new SineEase();

      protected UIModel UIModel
      {
         get
         {
            return (UIModel)DataContext;
         }
         private set
         {
            DataContext = value;
         }
      }

   }
}
