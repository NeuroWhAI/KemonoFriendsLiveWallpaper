namespace WallpaperManager
{
    partial class Form_Main
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다. 
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마세요.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form_Main));
            this.label1 = new System.Windows.Forms.Label();
            this.listBox_screens = new System.Windows.Forms.ListBox();
            this.comboBox_screens = new System.Windows.Forms.ComboBox();
            this.button_addWallpaper = new System.Windows.Forms.Button();
            this.contextMenuStrip_screenList = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.ToolStripMenuItem_removeScreen = new System.Windows.Forms.ToolStripMenuItem();
            this.button_hideManager = new System.Windows.Forms.Button();
            this.notifyIcon_tray = new System.Windows.Forms.NotifyIcon(this.components);
            this.contextMenuStrip_tray = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.ToolStripMenuItem_openManager = new System.Windows.Forms.ToolStripMenuItem();
            this.ToolStripMenuItem_exit = new System.Windows.Forms.ToolStripMenuItem();
            this.checkBox_autoRun = new System.Windows.Forms.CheckBox();
            this.contextMenuStrip_screenList.SuspendLayout();
            this.contextMenuStrip_tray.SuspendLayout();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(45, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "Screen";
            // 
            // listBox_screens
            // 
            this.listBox_screens.ContextMenuStrip = this.contextMenuStrip_screenList;
            this.listBox_screens.FormattingEnabled = true;
            this.listBox_screens.ItemHeight = 12;
            this.listBox_screens.Location = new System.Drawing.Point(12, 24);
            this.listBox_screens.Name = "listBox_screens";
            this.listBox_screens.Size = new System.Drawing.Size(245, 112);
            this.listBox_screens.TabIndex = 1;
            this.listBox_screens.MouseDown += new System.Windows.Forms.MouseEventHandler(this.listBox_screens_MouseDown);
            // 
            // comboBox_screens
            // 
            this.comboBox_screens.FormattingEnabled = true;
            this.comboBox_screens.Location = new System.Drawing.Point(12, 142);
            this.comboBox_screens.Name = "comboBox_screens";
            this.comboBox_screens.Size = new System.Drawing.Size(177, 20);
            this.comboBox_screens.TabIndex = 2;
            // 
            // button_addWallpaper
            // 
            this.button_addWallpaper.Location = new System.Drawing.Point(195, 139);
            this.button_addWallpaper.Name = "button_addWallpaper";
            this.button_addWallpaper.Size = new System.Drawing.Size(62, 24);
            this.button_addWallpaper.TabIndex = 3;
            this.button_addWallpaper.Text = "Add";
            this.button_addWallpaper.UseVisualStyleBackColor = true;
            this.button_addWallpaper.Click += new System.EventHandler(this.button_addWallpaper_Click);
            // 
            // contextMenuStrip_screenList
            // 
            this.contextMenuStrip_screenList.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.ToolStripMenuItem_removeScreen});
            this.contextMenuStrip_screenList.Name = "contextMenuStrip1";
            this.contextMenuStrip_screenList.Size = new System.Drawing.Size(118, 26);
            // 
            // ToolStripMenuItem_removeScreen
            // 
            this.ToolStripMenuItem_removeScreen.Name = "ToolStripMenuItem_removeScreen";
            this.ToolStripMenuItem_removeScreen.Size = new System.Drawing.Size(117, 22);
            this.ToolStripMenuItem_removeScreen.Text = "Remove";
            this.ToolStripMenuItem_removeScreen.Click += new System.EventHandler(this.ToolStripMenuItem_removeScreen_Click);
            // 
            // button_hideManager
            // 
            this.button_hideManager.Location = new System.Drawing.Point(12, 168);
            this.button_hideManager.Name = "button_hideManager";
            this.button_hideManager.Size = new System.Drawing.Size(245, 28);
            this.button_hideManager.TabIndex = 5;
            this.button_hideManager.Text = "Hide Manager";
            this.button_hideManager.UseVisualStyleBackColor = true;
            this.button_hideManager.Click += new System.EventHandler(this.button_hideManager_Click);
            // 
            // notifyIcon_tray
            // 
            this.notifyIcon_tray.BalloonTipIcon = System.Windows.Forms.ToolTipIcon.Info;
            this.notifyIcon_tray.ContextMenuStrip = this.contextMenuStrip_tray;
            this.notifyIcon_tray.Icon = ((System.Drawing.Icon)(resources.GetObject("notifyIcon_tray.Icon")));
            this.notifyIcon_tray.Text = "Kemono Friends Wallpaper";
            this.notifyIcon_tray.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.notifyIcon_tray_MouseDoubleClick);
            // 
            // contextMenuStrip_tray
            // 
            this.contextMenuStrip_tray.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.ToolStripMenuItem_openManager,
            this.ToolStripMenuItem_exit});
            this.contextMenuStrip_tray.Name = "contextMenuStrip_tray";
            this.contextMenuStrip_tray.Size = new System.Drawing.Size(104, 48);
            // 
            // ToolStripMenuItem_openManager
            // 
            this.ToolStripMenuItem_openManager.Name = "ToolStripMenuItem_openManager";
            this.ToolStripMenuItem_openManager.Size = new System.Drawing.Size(103, 22);
            this.ToolStripMenuItem_openManager.Text = "Open";
            this.ToolStripMenuItem_openManager.Click += new System.EventHandler(this.ToolStripMenuItem_openManager_Click);
            // 
            // ToolStripMenuItem_exit
            // 
            this.ToolStripMenuItem_exit.Name = "ToolStripMenuItem_exit";
            this.ToolStripMenuItem_exit.Size = new System.Drawing.Size(103, 22);
            this.ToolStripMenuItem_exit.Text = "Exit";
            this.ToolStripMenuItem_exit.Click += new System.EventHandler(this.ToolStripMenuItem_exit_Click);
            // 
            // checkBox_autoRun
            // 
            this.checkBox_autoRun.AutoSize = true;
            this.checkBox_autoRun.Location = new System.Drawing.Point(12, 202);
            this.checkBox_autoRun.Name = "checkBox_autoRun";
            this.checkBox_autoRun.Size = new System.Drawing.Size(174, 16);
            this.checkBox_autoRun.TabIndex = 7;
            this.checkBox_autoRun.Text = "Start when windows starts";
            this.checkBox_autoRun.UseVisualStyleBackColor = true;
            this.checkBox_autoRun.CheckedChanged += new System.EventHandler(this.checkBox_autoRun_CheckedChanged);
            // 
            // Form_Main
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(269, 228);
            this.Controls.Add(this.checkBox_autoRun);
            this.Controls.Add(this.button_hideManager);
            this.Controls.Add(this.button_addWallpaper);
            this.Controls.Add(this.comboBox_screens);
            this.Controls.Add(this.listBox_screens);
            this.Controls.Add(this.label1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "Form_Main";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Wallpaper Manager";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form_Main_FormClosing);
            this.Load += new System.EventHandler(this.Form_Main_Load);
            this.contextMenuStrip_screenList.ResumeLayout(false);
            this.contextMenuStrip_tray.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ListBox listBox_screens;
        private System.Windows.Forms.ComboBox comboBox_screens;
        private System.Windows.Forms.Button button_addWallpaper;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip_screenList;
        private System.Windows.Forms.ToolStripMenuItem ToolStripMenuItem_removeScreen;
        private System.Windows.Forms.Button button_hideManager;
        private System.Windows.Forms.NotifyIcon notifyIcon_tray;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip_tray;
        private System.Windows.Forms.ToolStripMenuItem ToolStripMenuItem_openManager;
        private System.Windows.Forms.ToolStripMenuItem ToolStripMenuItem_exit;
        private System.Windows.Forms.CheckBox checkBox_autoRun;
    }
}

