using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;

namespace WallpaperManager
{
    public class ScreenManager
    {
        static ScreenManager()
        {
            Reset();
        }

        //#################################################################################################################

        private static WinAPI.RECT s_combinedRect;

        public static WinAPI.MONITORINFO[] Screens
        { get; private set; }

        //#################################################################################################################

        public static void Reset()
        {
            s_combinedRect = new WinAPI.RECT(0, 0, 0, 0);

            List<WinAPI.MONITORINFO> screens = new List<WinAPI.MONITORINFO>();

            WinAPI.MonitorEnumDelegate callback = (IntPtr hDesktop, IntPtr hdc, ref WinAPI.RECT pRect, int d) =>
            {
                var info = new WinAPI.MONITORINFO();
                info.cbSize = sizeof(int) * 4 * 2 + sizeof(int) * 2;
                if (WinAPI.GetMonitorInfo(hDesktop, ref info) == false)
                    return false;

                var rect = info.rcMonitor;
                if (rect.Left < s_combinedRect.Left)
                    s_combinedRect.Left = rect.Left;
                if (rect.Top < s_combinedRect.Top)
                    s_combinedRect.Top = rect.Top;
                if (rect.Right > s_combinedRect.Right)
                    rect.Right = s_combinedRect.Right;
                if (rect.Bottom > s_combinedRect.Bottom)
                    rect.Bottom = s_combinedRect.Bottom;

                screens.Add(info);

                return true;
            };

            if (WinAPI.EnumDisplayMonitors(IntPtr.Zero, IntPtr.Zero, callback, 0))
            {
                Screens = screens.ToArray();
            }
            else
            {
                Screens = new[]
                {
                    new WinAPI.MONITORINFO()
                    {
                        rcMonitor = Screen.PrimaryScreen.Bounds,
                        rcWork = Screen.PrimaryScreen.WorkingArea,
                    }
                };
            }
        }

        //#################################################################################################################

        public static void FillScreen(IntPtr handle, WinAPI.MONITORINFO screen)
        {
            var rect = screen.rcMonitor;

            int x = rect.Left - s_combinedRect.Left;
            int y = rect.Top - s_combinedRect.Top;

            WinAPI.MoveWindow(handle, x, y, rect.Width, rect.Height, true);
        }

        public static bool FixBehindDesktopIcon(IntPtr formHandle)
        {
            IntPtr progman = WinAPI.FindWindow("Progman", null);

            if (progman == IntPtr.Zero)
                return false;


            IntPtr workerw = IntPtr.Zero;

            // 여러번 시도함.
            for (int step = 0; step < 8; ++step)
            {
                // 한번씩은 건너뜀.
                if (step % 2 == 0)
                {
                    IntPtr result = IntPtr.Zero;
                    WinAPI.SendMessageTimeout(progman,
                        0x052C,
                        new IntPtr(0),
                        IntPtr.Zero,
                        WinAPI.SendMessageTimeoutFlags.SMTO_NORMAL,
                        10000,
                        out result);
                }


                WinAPI.EnumWindows(new WinAPI.EnumWindowsProc((tophandle, topparamhandle) =>
                {
                    IntPtr p = WinAPI.FindWindowEx(tophandle,
                        IntPtr.Zero,
                        "SHELLDLL_DefView",
                        IntPtr.Zero);

                    if (p != IntPtr.Zero)
                    {
                        workerw = WinAPI.FindWindowEx(IntPtr.Zero,
                            tophandle,
                            "WorkerW",
                            IntPtr.Zero);
                    }

                    return true;
                }), IntPtr.Zero);


                if (workerw == IntPtr.Zero)
                {
                    Thread.Sleep(1000);
                }
                else
                {
                    break;
                }
            }

            if (workerw == IntPtr.Zero)
                return false;


            WinAPI.ShowWindow(workerw, 0/*HIDE*/);
            WinAPI.SetParent(formHandle, progman);


            return true;
        }
    }
}
