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
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // new_prefab
            // 
            this.new_prefab.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.new_prefab.Location = new System.Drawing.Point(291, 261);
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
            this.exit.Location = new System.Drawing.Point(291, 329);
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
            this.load_prefab.Location = new System.Drawing.Point(291, 295);
            this.load_prefab.Name = "load_prefab";
            this.load_prefab.Size = new System.Drawing.Size(127, 28);
            this.load_prefab.TabIndex = 1;
            this.load_prefab.Text = "Load Prefab";
            this.load_prefab.UseVisualStyleBackColor = true;
            this.load_prefab.Click += new System.EventHandler(this.LoadPrefab_Click);
            // 
            // label1
            // 
            this.label1.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 45F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(17, 35);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(615, 69);
            this.label1.TabIndex = 3;
            this.label1.Text = "Quick ‘n’ Dirty Studios";
            // 
            // label2
            // 
            this.label2.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 16F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(449, 104);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(167, 26);
            this.label2.TabIndex = 4;
            this.label2.Text = "Prefab Manager";
            // 
            // MainWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(658, 414);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.exit);
            this.Controls.Add(this.load_prefab);
            this.Controls.Add(this.new_prefab);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "MainWindow";
            this.Text = "Quick \'n\' Dirty Studios - Prefab Manager";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button new_prefab;
        private System.Windows.Forms.Button exit;
        private System.Windows.Forms.Button load_prefab;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
    }
}

