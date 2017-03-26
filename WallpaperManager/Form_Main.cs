using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;
using System.IO;

namespace WallpaperManager
{
    public partial class Form_Main : Form
    {
        public Form_Main()
        {
            InitializeComponent();
        }

        //###########################################################################################

        private Process m_wallpaper = null;
        private IntPtr m_wallpaperHandle = IntPtr.Zero;

        //###########################################################################################

        private void Form_Main_Load(object sender, EventArgs e)
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


            System.Threading.Thread.Sleep(100);


            for (int retry = 0; retry < 4; ++retry)
            {
                m_wallpaperHandle = WinAPI.FindWindow("SFML_Window", "Kemono Friends Live Wallpaper");

                if (m_wallpaperHandle == IntPtr.Zero)
                {
                    System.Threading.Thread.Sleep(1000);
                }
                else
                {
                    break;
                }
            }

            if (m_wallpaperHandle == IntPtr.Zero)
            {
                MessageBox.Show("Can\'t find wallpaper.", "Error!",
                    MessageBoxButtons.OK, MessageBoxIcon.Error);

                Application.Exit();
            }
        }
    }
}
