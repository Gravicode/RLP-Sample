using System;
using System.Collections;
using System.Threading;
using Microsoft.SPOT;
using Microsoft.SPOT.Presentation;
using Microsoft.SPOT.Presentation.Controls;
using Microsoft.SPOT.Presentation.Media;
using Microsoft.SPOT.Presentation.Shapes;
using Microsoft.SPOT.Touch;
using GHI.Processor;

using Gadgeteer.Networking;
using GT = Gadgeteer;
using GTM = Gadgeteer.Modules;

namespace RlpSample
{
    public partial class Program
    {
        // This method is run when the mainboard is powered up or reset.   
        void ProgramStarted()
        {
            Debug.Print("Program Started");
            GT.Timer timer = new GT.Timer(3000); 
            timer.Tick += Timer_Tick;
            timer.Start();
           }

        private void Timer_Tick(GT.Timer timer)
        {
            byte[] elfBuffer = Resources.GetBytes(Resources.BinaryResources.G120RLP); //Make sure to load the ELF file you compiled into this array.

            var elfImage = new RuntimeLoadableProcedures.ElfImage(elfBuffer);

            var yourFunction = elfImage.FindFunction("TestFungsi");
            var arr = new byte[] { 1, 2, 3, 4, 5 };
            var result = yourFunction.Invoke(10, 3, arr);

            Debug.Print("Hasil invoke fungsi " + result.ToString()); //Should be 5
            Debug.Print("Nilai array ke 0 = " + arr[0].ToString()); //Should be 5

        }
    }
}
