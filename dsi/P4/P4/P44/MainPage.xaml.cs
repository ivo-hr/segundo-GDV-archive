using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.ApplicationModel.DataTransfer;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
using Windows.Devices.Input;
using Windows.UI.Input;
using Windows.UI.Core;
using Windows.Gaming.Input;
// La plantilla de elemento Página en blanco está documentada en https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0xc0a

namespace P4
{
    /// <summary>
    /// Página vacía que se puede usar de forma independiente o a la que se puede navegar dentro de un objeto Frame.
    /// </summary>

    public sealed partial class MainPage : Page
    {

        public ObservableCollection<VMDron> ListaDrones { get; } = new ObservableCollection<VMDron>();
        //Transform while  dragging
        private TranslateTransform dragTr;
        //Pin, hand and arrow cursors
        CoreCursor pCur;
        CoreCursor hCur;
        CoreCursor aCur;
        //Mouse buttons
        bool lmb = false;
        bool rmb = false;
        //Current drone to do stuff on
        int currD;
        //Point of the  pointer
        PointerPoint ptrPt;

        public MainPage()
        {
            this.InitializeComponent();
            dragTr = new TranslateTransform();
            MiDron.RenderTransform = this.dragTr;

            pCur = new CoreCursor(CoreCursorType.Pin, 0);
            hCur = new CoreCursor(CoreCursorType.Hand, 0);
            aCur = new CoreCursor(CoreCursorType.Arrow, 0);
        }
        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            // Cosntruye las listas de ModelView a partir de la lista Modelo 
            if (ListaDrones != null)
                foreach (Dron dron in Model.GetAllDrones())
                {
                    VMDron VMitem = new VMDron(dron);
                    ListaDrones.Add(VMitem);
                }
            base.OnNavigatedTo(e);
        }
        //Drone dragging init
        private void Dron_Drag(object sender, DragEventArgs e)
        {
            e.AcceptedOperation = DataPackageOperation.Copy;
        }
        //Drone drag movement behaviour
        private void MyDron_Manipulation(object sender, ManipulationDeltaRoutedEventArgs e)
        {
            dragTr.X += e.Delta.Translation.X;
            dragTr.Y += e.Delta.Translation.Y;
        }
        //Drone drop behaviour
        private async void Dron_Drop(object sender, DragEventArgs e)
        {
            var id = await e.DataView.GetTextAsync();
            var number = int.Parse(id);

            MiDron.Source = ListaDrones[number].Img.Source;
            Point pos = e.GetPosition(MyMap);


            MiDron.Visibility = Visibility.Visible;
            dragTr.X = pos.X - 25;
            dragTr.Y = pos.Y - 15;

            MiImagen.Source = ListaDrones[number].Img.Source;
            Texto.Text = ListaDrones[number].Explicacion;
        }
        //Start drag across the map
        private void ImageGridView_DragItemsInit(object sender, DragItemsStartingEventArgs e)
        {
            VMDron dron = e.Items[0] as VMDron;
            string id = dron.Id.ToString();
            e.Data.SetText(id);
            e.Data.RequestedOperation = DataPackageOperation.Copy;
        }
        //Pointer modifier and state
        private void MyDronPointPr(object sender, PointerRoutedEventArgs e)
        {
            ptrPt = e.GetCurrentPoint(MyMap);

            if (ptrPt.Properties.IsRightButtonPressed)
            {
                rmb = true;
                Window.Current.CoreWindow.PointerCursor = hCur;
            }

            else if (ptrPt.Properties.IsLeftButtonPressed)
            {
                lmb = true;
                Window.Current.CoreWindow.PointerCursor = pCur;
            }
        }
        //Drone movement depending on pointer
        private void MyDronPointMov(object sender, PointerRoutedEventArgs e)
        {
            PointerPoint newPt = e.GetCurrentPoint(MyMap);
            if (lmb)
            {
                ListaDrones[currD].X = (int)newPt.Position.X;
                ListaDrones[currD].Y = (int)newPt.Position.Y;

                ListaDrones[currD].Transf.TranslateX = ListaDrones[currD].X - 20;
                ListaDrones[currD].Transf.TranslateY = ListaDrones[currD].Y - 15;
                MiDron.RenderTransform = ListaDrones[currD].Transf;

            }
            if (rmb)
            {
                ListaDrones[currD].Angl = (int)newPt.Position.X - (int)ptrPt.Position.X;
                ListaDrones[currD].Transf.Rotation = ListaDrones[currD].Angl;
                ListaDrones[currD].Transf.CenterX = 20;
                ListaDrones[currD].Transf.CenterY = 15;
                MiDron.RenderTransform = ListaDrones[currD].Transf;

            }
        }
        //Drone release depending on  button press
        private void MyDronPointRel(object sender, PointerRoutedEventArgs e)
        {
            PointerPoint ptrPt = e.GetCurrentPoint(MyMap);
            if (!ptrPt.Properties.IsLeftButtonPressed) lmb = false;
            if (!ptrPt.Properties.IsRightButtonPressed) rmb = false;
            Window.Current.CoreWindow.PointerCursor = aCur;

        }
        //Drone position assignment upon dropping in the  map
        private async void MyCanvasDrop(object sender, DragEventArgs e)
        {
            Point dronPt = e.GetPosition(MiCanvas);
            var id = await e.DataView.GetTextAsync();
            currD = int.Parse(id);
            MiDron.Source = ListaDrones[currD].Img.Source;
            ListaDrones[currD].X = (int)dronPt.X;
            ListaDrones[currD].Y = (int)dronPt.Y;

            ListaDrones[currD].Transf.Rotation = ListaDrones[currD].Angl;
            ListaDrones[currD].Transf.CenterX = 20;
            ListaDrones[currD].Transf.CenterY = 15;
            ListaDrones[currD].Transf.TranslateX = ListaDrones[currD].X - 20;
            ListaDrones[currD].Transf.TranslateY = ListaDrones[currD].Y - 15;
            MiDron.RenderTransform = ListaDrones[currD].Transf;
        }
        //Drag over the map
        private void MyCanvasDragO(object sender, DragEventArgs e)
        {
            e.AcceptedOperation = DataPackageOperation.Copy;
        }
        //Drone  control upon key/button press
        private void MyDronContCtrl_KD(object sender, KeyRoutedEventArgs e)
        {

            float ZoomFactor = MainImageScroller.ZoomFactor;

            switch (e.Key)
            {
                case Windows.System.VirtualKey.W:
                case Windows.System.VirtualKey.GamepadRightThumbstickUp:
                    ListaDrones[currD].Transf.TranslateY -= 5;
                    MyDronContCtrl.RenderTransform = ListaDrones[currD].Transf;
                    break;

                case Windows.System.VirtualKey.A:
                case Windows.System.VirtualKey.GamepadRightThumbstickLeft:
                    ListaDrones[currD].Transf.TranslateX -= 5;
                    MyDronContCtrl.RenderTransform = ListaDrones[currD].Transf;
                    break;

                case Windows.System.VirtualKey.S:
                case Windows.System.VirtualKey.GamepadRightThumbstickDown:
                    ListaDrones[currD].Transf.TranslateY += 5;
                    MyDronContCtrl.RenderTransform = ListaDrones[currD].Transf;
                    break;

                case Windows.System.VirtualKey.D:
                case Windows.System.VirtualKey.GamepadRightThumbstickRight:
                    ListaDrones[currD].Transf.TranslateX += 5;
                    MyDronContCtrl.RenderTransform = ListaDrones[currD].Transf;
                    break;

                case Windows.System.VirtualKey.Q:
                case Windows.System.VirtualKey.GamepadLeftTrigger:
                    ListaDrones[currD].Transf.Rotation -= 5;
                    MyDronContCtrl.RenderTransform = ListaDrones[currD].Transf;
                    break;

                case Windows.System.VirtualKey.E:
                case Windows.System.VirtualKey.GamepadRightTrigger:
                    ListaDrones[currD].Transf.Rotation += 5;
                    MyDronContCtrl.RenderTransform = ListaDrones[currD].Transf;
                    break;

                case Windows.System.VirtualKey.GamepadLeftShoulder:
                    MainImageScroller.ChangeView(null, null, (float)ZoomFactor * 0.9f);
                    break;

                case Windows.System.VirtualKey.GamepadRightShoulder:
                    MainImageScroller.ChangeView(null, null, (float)ZoomFactor * 1.1f);
                    break;
            }
        }
        //Tab switching between menus
        private void CommandBar_KD(object sender, KeyRoutedEventArgs e)
        {
            if (e.Key == Windows.System.VirtualKey.Tab)
            {
                e.Handled = true;
                DependencyObject nextMenu = FocusManager.FindNextFocusableElement(FocusNavigationDirection.Down); ;
                
                (nextMenu as Control).Focus(FocusState.Keyboard);
            }
        }
        //Drone selection from drone menu
        private void ImageGridView_ItemClick(object sender, ItemClickEventArgs e)
        {
            VMDron clkd = e.ClickedItem as VMDron;
            if (clkd != null)
            {
                currD = clkd.Id;
                int x = ListaDrones[currD].X;
                int y = ListaDrones[currD].Y;
                int ang = ListaDrones[currD].Angl;
                MiDron.Source = ListaDrones[currD].Img.Source;
                ListaDrones[currD].Transf.Rotation = ang;
                ListaDrones[currD].Transf.CenterX = 20;
                ListaDrones[currD].Transf.CenterY = 15;
                ListaDrones[currD].Transf.TranslateX = x - 20;
                ListaDrones[currD].Transf.TranslateY = y - 15;
                MyDronContCtrl.RenderTransform = ListaDrones[currD].Transf;
            }
        }
    }
}
