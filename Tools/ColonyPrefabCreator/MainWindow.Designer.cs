namespace ColonyPrefabCreator
{
    partial class MainWindow
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainWindow));
            this.new_prefab = new System.Windows.Forms.Button();
            this.exit = new System.Windows.Forms.Button();
            this.load_prefab = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.LoadPrefabDialog = new System.Windows.Forms.OpenFileDialog();
            this.TheColony = new System.Windows.Forms.PictureBox();
            this.Background = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.TheColony)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Background)).BeginInit();
            this.SuspendLayout();
            // 
            // new_prefab
            // 
            this.new_prefab.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.new_prefab.Location = new System.Drawing.Point(340, 341);
            this.new_prefab.Name = "new_prefab";
            this.new_prefab.Size = new System.Drawing.Size(127, 28);
            this.new_prefab.TabIndex = 0;
            this.new_prefab.Text = "New Prefab";
            this.new_prefab.UseVisualStyleBackColor = true;
            this.new_prefab.Click += new System.EventHandler(this.NewPrefab_Click);
            // 
            // exit
            // 
            this.exit.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.exit.Location = new System.Drawing.Point(340, 409);
            this.exit.Name = "exit";
            this.exit.Size = new System.Drawing.Size(127, 28);
            this.exit.TabIndex = 2;
            this.exit.Text = "Exit";
            this.exit.UseVisualStyleBackColor = true;
            this.exit.Click += new System.EventHandler(this.Exit_Click);
            // 
            // load_prefab
            // 
            this.load_prefab.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.load_prefab.Location = new System.Drawing.Point(340, 375);
            this.load_prefab.Name = "load_prefab";
            this.load_prefab.Size = new System.Drawing.Size(127, 28);
            this.load_prefab.TabIndex = 1;
            this.load_prefab.Text = "Load Prefab";
            this.load_prefab.UseVisualStyleBackColor = true;
            this.load_prefab.Click += new System.EventHandler(this.LoadPrefab_Click);
            // 
            // label2
            // 
            this.label2.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 16F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.label2.Location = new System.Drawing.Point(444, 206);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(167, 26);
            this.label2.TabIndex = 4;
            this.label2.Text = "Prefab Manager";
            this.label2.Click += new System.EventHandler(this.label2_Click);
            // 
            // LoadPrefabDialog
            // 
            this.LoadPrefabDialog.FileName = "openFileDialog1";
            // 
            // TheColony
            // 
            this.TheColony.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.TheColony.Image = global::ColonyPrefabManager.Properties.Resources.the_colony2;
            this.TheColony.Location = new System.Drawing.Point(158, 24);
            this.TheColony.Name = "TheColony";
            this.TheColony.Size = new System.Drawing.Size(453, 179);
            this.TheColony.TabIndex = 6;
            this.TheColony.TabStop = false;
            // 
            // Background
            // 
            this.Background.BackgroundImage = global::ColonyPrefabManager.Properties.Resources._612136;
            this.Background.Dock = System.Windows.Forms.DockStyle.Fill;
            this.Background.InitialImage = ((System.Drawing.Image)(resources.GetObject("Background.InitialImage")));
            this.Background.Location = new System.Drawing.Point(0, 0);
            this.Background.Name = "Background";
            this.Background.Size = new System.Drawing.Size(763, 488);
            this.Background.TabIndex = 5;
            this.Background.TabStop = false;
            // 
            // MainWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(763, 488);
            this.Controls.Add(this.TheColony);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.exit);
            this.Controls.Add(this.load_prefab);
            this.Controls.Add(this.new_prefab);
            this.Controls.Add(this.Background);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "MainWindow";
            this.Text = "Quick \'n\' Dirty Studios - Prefab Manager";
            ((System.ComponentModel.ISupportInitialize)(this.TheColony)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Background)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button new_prefab;
        private System.Windows.Forms.Button exit;
        private System.Windows.Forms.Button load_prefab;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.OpenFileDialog LoadPrefabDialog;
        private System.Windows.Forms.PictureBox Background;
        private System.Windows.Forms.PictureBox TheColony;
    }
}

