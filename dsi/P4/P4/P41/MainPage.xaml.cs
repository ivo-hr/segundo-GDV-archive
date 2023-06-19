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
        public MainPage()
        {
            this.InitializeComponent();
            dragTr = new TranslateTransform();
            MiDron.RenderTransform = this.dragTr;
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
            VMDron item = e.Items[0] as VMDron;
            string id = item.Id.ToString();
            e.Data.SetText(id);
            e.Data.RequestedOperation = DataPackageOperation.Copy;
        }
    }
}
