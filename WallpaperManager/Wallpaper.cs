using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using System.Diagnostics;
using System.IO;

namespace WallpaperManager
{
    public class Wallpaper
    {
        public Wallpaper()
        {

        }

        //###########################################################################################

        private Process m_wallpaper = null;
        private IntPtr m_wallpaperHandle = IntPtr.Zero;
        public IntPtr Handle
        {
            get
            {
                return m_wallpaperHandle;
            }
        }

        private int m_screenNumber = 0;
        public int ScreenNumber
        {
            get
            {
                return m_screenNumber;
            }
            set
            {
                if (value < 0)
                    value = 0;
                else if (value >= ScreenManager.Screens.Length)
                    value = 0;

                m_screenNumber = value;

                PinToDesktop(value);
            }
        }

        private Task m_checkParent = null;
        private bool m_onRunning = false;
        private EventWaitHandle m_waitHandle = null;

        //###########################################################################################

        public bool StartWallpaper()
        {
            string current = Directory.GetCurrentDirectory();

            string wallpaperFile = "KemonoFriendsLiveWallpaper.exe";
#if DEBUG
            wallpaperFile = current + "/../../../Debug/KemonoFriendsLiveWallpaper.exe";
#endif

            m_wallpaper = Process.Start(new ProcessStartInfo(wallpaperFile)
            {
                Arguments = "NeuroWhAI",
                WorkingDirectory = Path.GetDirectoryName(Path.GetFullPath(wallpaperFile)),
                CreateNoWindow = true,
                UseShellExecute = false,
            });


            for (int retry = 0; retry < 125; ++retry)
            {
                m_wallpaperHandle = WinAPI.FindWindow("SFML_Window", "Kemono Friends Live Wallpaper");

                if (m_wallpaperHandle == IntPtr.Zero)
                {
                    Thread.Sleep(80);
                }
                else
                {
                    break;
                }
            }

            if (m_wallpaperHandle == IntPtr.Zero)
            {
                if (m_wallpaper.HasExited == false)
                {
                    m_wallpaper.Kill();
                    m_wallpaper = null;
                }


                return false;
            }
            else
            {
                // Hide taskbar icon and border.
                WinAPI.ShowWindow(m_wallpaperHandle, 0); // HIDE
                var exStyle = WinAPI.GetWindowLong(m_wallpaperHandle, WinAPI.GWL_EXSTYLE);
                exStyle |= WinAPI.WS_EX_TOOLWINDOW;
                exStyle &= ~WinAPI.WS_EX_APPWINDOW;
                exStyle &= ~WinAPI.WS_EX_DLGMODALFRAME;
                exStyle &= ~WinAPI.WS_EX_CLIENTEDGE;
                exStyle &= ~WinAPI.WS_EX_STATICEDGE;
                WinAPI.SetWindowLong(m_wallpaperHandle, WinAPI.GWL_EXSTYLE, exStyle);
                WinAPI.ShowWindow(m_wallpaperHandle, 5); // SHOW to apply new style.


                PinToDesktop(this.ScreenNumber);


                m_waitHandle = new EventWaitHandle(false, EventResetMode.ManualReset);
                m_onRunning = true;
                m_checkParent = Task.Factory.StartNew(CheckWallpaper, m_wallpaperHandle);


                return true;
            }
        }

        public void StopWallpaper()
        {
            if (m_wallpaperHandle != IntPtr.Zero && m_wallpaper.HasExited == false)
            {
                // Send WM_CLOSE.
                WinAPI.PostMessage(m_wallpaperHandle, 0x0010, IntPtr.Zero, IntPtr.Zero);
            }

            m_wallpaper = null;
            m_wallpaperHandle = IntPtr.Zero;


            if (m_checkParent != null)
            {
                m_onRunning = false;
                m_waitHandle.Set();
                m_checkParent.Wait(TimeSpan.FromSeconds(4.0));
                m_checkParent = null;

                m_waitHandle.Dispose();
                m_waitHandle = null;
            }
        }

        private void PinToDesktop(int screenNumber)
        {
            if (m_wallpaperHandle != IntPtr.Zero)
            {
                ScreenManager.FillScreen(m_wallpaperHandle, ScreenManager.Screens[screenNumber]);
                ScreenManager.FixBehindDesktopIcon(m_wallpaperHandle);
            }
        }

        private void CheckWallpaper(object thisHandle)
        {
            IntPtr me = (IntPtr)thisHandle;


            while (m_onRunning)
            {
                bool isChildOfProgman = false;


                var progman = WinAPI.FindWindow("Progman", null);

                WinAPI.EnumChildWindows(progman, new WinAPI.EnumWindowsProc((handle, lparam) =>
                {
                    if (handle == me)
                    {
                        isChildOfProgman = true;
                        return false;
                    }

                    return true;
                }), IntPtr.Zero);


                if (isChildOfProgman == false)
                {
                    PinToDesktop(this.ScreenNumber);
                }


                m_waitHandle.WaitOne(1000);
            }
        }
    }
}
