namespace BeneDGSResultUtility
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.btn_install = new System.Windows.Forms.Button();
            this.btn_uninstall = new System.Windows.Forms.Button();
            this.btn_start = new System.Windows.Forms.Button();
            this.btn_stop = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // btn_install
            // 
            this.btn_install.Location = new System.Drawing.Point(106, 60);
            this.btn_install.Name = "btn_install";
            this.btn_install.Size = new System.Drawing.Size(106, 34);
            this.btn_install.TabIndex = 0;
            this.btn_install.Text = "安装服务";
            this.btn_install.UseVisualStyleBackColor = true;
            this.btn_install.Click += new System.EventHandler(this.btn_install_Click);
            // 
            // btn_uninstall
            // 
            this.btn_uninstall.Location = new System.Drawing.Point(106, 109);
            this.btn_uninstall.Name = "btn_uninstall";
            this.btn_uninstall.Size = new System.Drawing.Size(106, 34);
            this.btn_uninstall.TabIndex = 0;
            this.btn_uninstall.Text = "卸载服务";
            this.btn_uninstall.UseVisualStyleBackColor = true;
            this.btn_uninstall.Click += new System.EventHandler(this.btn_uninstall_Click);
            // 
            // btn_start
            // 
            this.btn_start.Location = new System.Drawing.Point(106, 158);
            this.btn_start.Name = "btn_start";
            this.btn_start.Size = new System.Drawing.Size(106, 34);
            this.btn_start.TabIndex = 0;
            this.btn_start.Text = "启动服务";
            this.btn_start.UseVisualStyleBackColor = true;
            this.btn_start.Click += new System.EventHandler(this.btn_start_Click);
            // 
            // btn_stop
            // 
            this.btn_stop.Location = new System.Drawing.Point(106, 207);
            this.btn_stop.Name = "btn_stop";
            this.btn_stop.Size = new System.Drawing.Size(106, 34);
            this.btn_stop.TabIndex = 0;
            this.btn_stop.Text = "停止服务";
            this.btn_stop.UseVisualStyleBackColor = true;
            this.btn_stop.Click += new System.EventHandler(this.btn_stop_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(318, 305);
            this.Controls.Add(this.btn_stop);
            this.Controls.Add(this.btn_start);
            this.Controls.Add(this.btn_uninstall);
            this.Controls.Add(this.btn_install);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Form1";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btn_install;
        private System.Windows.Forms.Button btn_uninstall;
        private System.Windows.Forms.Button btn_start;
        private System.Windows.Forms.Button btn_stop;
    }
}

