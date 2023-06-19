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
        //Timer for input delay
        DispatcherTimer timer;
        //All  controllers
        private List<Gamepad> allXbox = new List<Gamepad>();
        //current controller
        private Gamepad currXbox;
        //Controller on which we locked on
        private readonly object lockOnXbox =  new object();
        //Controller input reader
        private GamepadReading readXbox;
        //Controller vibration feature
        private GamepadVibration rumbleXbox;
        


        public MainPage()
        {
            this.InitializeComponent();
            dragTr = new TranslateTransform();
            MiDron.RenderTransform = this.dragTr;

            pCur = new CoreCursor(CoreCursorType.Pin, 0);
            hCur = new CoreCursor(CoreCursorType.Hand, 0);
            aCur = new CoreCursor(CoreCursorType.Arrow, 0);

            //To lock on/unlock from the current controller
            Gamepad.GamepadAdded += (object sender, Gamepad e) =>
            {
                lock (lockOnXbox)
                {
                    bool regXbox = allXbox.Contains(e);

                    if (!regXbox)
                    {
                        allXbox.Add(e);
                        currXbox = allXbox[0];
                    }
                }
            };
            Gamepad.GamepadRemoved += (object sender, Gamepad e) =>
            {
                lock (lockOnXbox)
                {
                    int delXbox = allXbox.IndexOf(e);

                    if (delXbox > -1)
                    {
                        if (currXbox == allXbox[delXbox]) currXbox = null;


                        allXbox.RemoveAt(delXbox);
                    }
                }
            };
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
            XboxTimerStart();
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
            var dronID = await e.DataView.GetTextAsync();
            var dronN = int.Parse(dronID);

            MiDron.Source = ListaDrones[dronN].Img.Source;
            Point pos = e.GetPosition(MyMap);


            MiDron.Visibility = Visibility.Visible;
            dragTr.X = pos.X - 25;
            dragTr.Y = pos.Y - 15;

            MiImagen.Source = ListaDrones[dronN].Img.Source;
            Texto.Text = ListaDrones[dronN].Explicacion;
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
            PointerPoint currPt = e.GetCurrentPoint(MyMap);
            if (lmb)
            {
                ListaDrones[currD].X = (int)currPt.Position.X;
                ListaDrones[currD].Y = (int)currPt.Position.Y;

                ListaDrones[currD].Transf.TranslateX = ListaDrones[currD].X - 20;
                ListaDrones[currD].Transf.TranslateY = ListaDrones[currD].Y - 15;
                MiDron.RenderTransform = ListaDrones[currD].Transf;

            }
            if (rmb)
            {
                ListaDrones[currD].Angl = (int)currPt.Position.X - (int)ptrPt.Position.X;
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
                //case Windows.System.VirtualKey.GamepadRightThumbstickUp:
                    ListaDrones[currD].Transf.TranslateY -= 5;
                    MyDronContCtrl.RenderTransform = ListaDrones[currD].Transf;
                    break;

                case Windows.System.VirtualKey.A:
                //case Windows.System.VirtualKey.GamepadRightThumbstickLeft:
                    ListaDrones[currD].Transf.TranslateX -= 5;
                    MyDronContCtrl.RenderTransform = ListaDrones[currD].Transf;
                    break;

                case Windows.System.VirtualKey.S:
                //case Windows.System.VirtualKey.GamepadRightThumbstickDown:
                    ListaDrones[currD].Transf.TranslateY += 5;
                    MyDronContCtrl.RenderTransform = ListaDrones[currD].Transf;
                    break;

                case Windows.System.VirtualKey.D:
                //case Windows.System.VirtualKey.GamepadRightThumbstickRight:
                    ListaDrones[currD].Transf.TranslateX += 5;
                    MyDronContCtrl.RenderTransform = ListaDrones[currD].Transf;
                    break;

                case Windows.System.VirtualKey.Q:
                //case Windows.System.VirtualKey.GamepadLeftTrigger:
                    ListaDrones[currD].Transf.Rotation -= 5;
                    MyDronContCtrl.RenderTransform = ListaDrones[currD].Transf;
                    break;

                case Windows.System.VirtualKey.E:
                //case Windows.System.VirtualKey.GamepadRightTrigger:
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
                DependencyObject nextMenu = FocusManager.FindNextFocusableElement(FocusNavigationDirection.Down);
                (nextMenu as Control).Focus(FocusState.Keyboard);
            }
        }
        //Drone selection from drone menu
        private void ImageGridView_ItemClick(object sender, ItemClickEventArgs e)
        {
            if (e.ClickedItem is VMDron clkd)
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
        //Controller input reader
        void XboxReader()
        {
            readXbox = currXbox.GetCurrentReading();

            //Joystick deadzones
            if (readXbox.RightThumbstickX > 0.3)
                readXbox.RightThumbstickX -= 0.3;
            else if (readXbox.RightThumbstickX < -0.3)
                readXbox.RightThumbstickX += 0.3;
            else
                readXbox.RightThumbstickX = 0;

            if (readXbox.RightThumbstickY > 0.3)
                readXbox.RightThumbstickY -= 0.3;
            else if (readXbox.RightThumbstickY < -0.3)
                readXbox.RightThumbstickY += 0.3;
            else
                readXbox.RightThumbstickY = 0;
        }
        //Controller vibration feature
        void XboxRumble()
        {
            if (readXbox.LeftTrigger > 0 || 
                readXbox.RightTrigger > 0)
                rumbleXbox.LeftMotor = 1;

            else
                rumbleXbox.LeftMotor = 0.0;

            if (readXbox.RightThumbstickX != 0 ||
               readXbox.RightThumbstickY != 0)
                rumbleXbox.RightMotor = 1;

            else
                rumbleXbox.RightMotor = 0.0;


            currXbox.Vibration = rumbleXbox;
        }
        //Controller control upon current drone
        void XboxInteraction()
        {
            if ((currXbox != null) && (currD >= 0) &&
                (MyDronContCtrl.FocusState != FocusState.Unfocused))
            {
                double x = ListaDrones[currD].X;
                double y = ListaDrones[currD].Y;
                double ang = ListaDrones[currD].Angl;

                x += 10 * readXbox.RightThumbstickX;
                y -= 10 * readXbox.RightThumbstickY;

                ang += (3 * readXbox.RightTrigger);
                ang -= (3 * readXbox.LeftTrigger);


                ListaDrones[currD].X = (int)x;
                ListaDrones[currD].Y = (int)y;
                ListaDrones[currD].Angl = (int)ang;
                ListaDrones[currD].Transf.Rotation = ListaDrones[currD].Angl;
                ListaDrones[currD].Transf.CenterX = 20;
                ListaDrones[currD].Transf.CenterY = 15;
                ListaDrones[currD].Transf.TranslateX = ListaDrones[currD].X - 20;
                ListaDrones[currD].Transf.TranslateY = ListaDrones[currD].Y - 15;

                MyDronContCtrl.RenderTransform = ListaDrones[currD].Transf;
            }
        }
        //Controller reading start + interval between reads
        public void XboxTimerStart()
        {
            timer = new DispatcherTimer();
            timer.Tick += XboxTick;
            timer.Interval = new TimeSpan(100000);
            timer.Start();
        }
        //Controller full function

        void XboxTick(object sender, object e)
        {
            if(currXbox != null)
            {
                XboxReader();
                XboxInteraction();
                XboxRumble();
            }
        }
    }
}
