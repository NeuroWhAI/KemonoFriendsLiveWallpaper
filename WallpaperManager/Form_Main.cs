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
using Microsoft.Win32;

namespace WallpaperManager
{
    public partial class Form_Main : Form
    {
        public Form_Main()
        {
            InitializeComponent();
        }

        //###########################################################################################

        private readonly string AppName = "NeuroWhAI_KEMONO_LIVE_WALLPAPER_TANOSHII";

        private List<Wallpaper> m_wallpapers = new List<Wallpaper>();
        private Option m_option = new Option();
        private readonly string OptionFileName = "Option.dat";

        //###########################################################################################

        private void Form_Main_Load(object sender, EventArgs e)
        {
            m_option.LoadFromFile(OptionFileName);

            this.checkBox_autoRun.Checked = m_option.AutoRun;

            for (int i = 0; i < m_option.ScreenNumbers.Count; ++i)
            {
                int num = m_option.ScreenNumbers[i];

                bool success = AddWallpaper(new Wallpaper()
                {
                    ScreenNumber = num,
                });

                if (success)
                {
                    this.listBox_screens.Items.Add(string.Format("Screen {0}", num + 1));
                }
                else
                {
                    // Invalid screen number.
                    m_option.ScreenNumbers[i] = -1;
                }
            }

            // Remove invalid screen number.
            m_option.ScreenNumbers.RemoveAll(x => x < 0);
            m_option.SaveToFile(OptionFileName);


            foreach (int screenNumber in Enumerable.Range(0, ScreenManager.Screens.Length))
            {
                if (m_option.ScreenNumbers.Any(idx => idx == screenNumber))
                    continue;

                this.comboBox_screens.Items.Add(string.Format("Screen {0}", screenNumber + 1));
            }
        }

        private void Form_Main_FormClosing(object sender, FormClosingEventArgs e)
        {
            m_option.SaveToFile(OptionFileName);


            this.notifyIcon_tray.Visible = false;


            foreach (var wallpaper in m_wallpapers)
            {
                wallpaper.StopWallpaper();
            }
        }

        private void button_addWallpaper_Click(object sender, EventArgs e)
        {
            if (this.comboBox_screens.SelectedIndex >= 0)
            {
                string targetScreen = this.comboBox_screens.SelectedItem as string;


                int screenNumber = int.Parse(targetScreen.Split(' ')[1]) - 1;

                bool success = AddWallpaper(new Wallpaper()
                {
                    ScreenNumber = screenNumber,
                });


                if (success)
                {
                    this.listBox_screens.Items.Add(targetScreen);
                    this.comboBox_screens.Items.RemoveAt(this.comboBox_screens.SelectedIndex);
                }
                else
                {
                    MessageBox.Show("Fail to set wallpaper.", "Error!",
                        MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
        }

        private void ToolStripMenuItem_removeScreen_Click(object sender, EventArgs e)
        {
            if (this.listBox_screens.SelectedIndex >= 0)
            {
                string targetScreen = this.listBox_screens.SelectedItem as string;


                int screenNumber = int.Parse(targetScreen.Split(' ')[1]) - 1;

                RemoveWallpaperInScreen(screenNumber);


                this.comboBox_screens.Items.Add(targetScreen);
                this.listBox_screens.Items.RemoveAt(this.listBox_screens.SelectedIndex);
            }
        }

        private void listBox_screens_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Right)
            {
                int index = this.listBox_screens.IndexFromPoint(e.Location);
                if (index >= 0 && index < this.listBox_screens.Items.Count)
                {
                    this.listBox_screens.SelectedIndex = index;
                }
            }
        }

        private void button_hideManager_Click(object sender, EventArgs e)
        {
            this.Hide();
            this.notifyIcon_tray.Visible = true;

            // FIXME: Pin wallpaper again.
        }

        private void notifyIcon_tray_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            this.notifyIcon_tray.Visible = false;
            this.Show();
            this.Activate();
        }

        private void ToolStripMenuItem_openManager_Click(object sender, EventArgs e)
        {
            this.notifyIcon_tray.Visible = false;
            this.Show();
            this.Activate();
        }

        private void ToolStripMenuItem_exit_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void checkBox_autoRun_CheckedChanged(object sender, EventArgs e)
        {
            using (var key = Registry.CurrentUser.OpenSubKey(@"SOFTWARE\Microsoft\Windows\CurrentVersion\Run", true))
            {
                if (this.checkBox_autoRun.Checked)
                {
                    key.SetValue(AppName, Application.ExecutablePath);
                }
                else
                {
                    key.DeleteValue(AppName, false);
                }
            }


            m_option.AutoRun = this.checkBox_autoRun.Checked;
            m_option.SaveToFile(OptionFileName);
        }

        //###########################################################################################

        private bool AddWallpaper(Wallpaper wallpaper)
        {
            if (m_wallpapers.Any(wp => wp.ScreenNumber == wallpaper.ScreenNumber))
            {
                return false;
            }


            bool success = wallpaper.StartWallpaper();
            
            this.Activate();

            if (success)
            {
                m_wallpapers.Add(wallpaper);


                if (m_option.ScreenNumbers.Any(x => x == wallpaper.ScreenNumber) == false)
                {
                    m_option.ScreenNumbers.Add(wallpaper.ScreenNumber);
                }
                m_option.SaveToFile(OptionFileName);
            }
            else
            {
                wallpaper.StopWallpaper();
            }


            return success;
        }

        private bool RemoveWallpaperInScreen(int screenNumber)
        {
            int index = m_wallpapers.FindIndex(wp => wp.ScreenNumber == screenNumber);

            if (index >= 0)
            {
                m_wallpapers[index].StopWallpaper();

                m_wallpapers.RemoveAt(index);


                m_option.ScreenNumbers.RemoveAll(x => x == screenNumber);
                m_option.SaveToFile(OptionFileName);


                return true;
            }

            return false;
        }
    }
}
