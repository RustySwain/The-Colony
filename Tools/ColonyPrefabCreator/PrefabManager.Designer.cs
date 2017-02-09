using System;

namespace ColonyPrefabManager
{
    partial class PrefabManager
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(PrefabManager));
            this.AddComponent = new System.Windows.Forms.Button();
            this.ComponentList = new System.Windows.Forms.ComboBox();
            this.GameObject_ID_Input = new System.Windows.Forms.NumericUpDown();
            this.GameObject_ID_Label = new System.Windows.Forms.Label();
            this.GameObject_Name_Label = new System.Windows.Forms.Label();
            this.GameObject_Name_Input = new System.Windows.Forms.TextBox();
            this.GameObject_Tag_Label = new System.Windows.Forms.Label();
            this.GameObject_Tag_Input = new System.Windows.Forms.TextBox();
            this.GameObject_Transperent = new System.Windows.Forms.CheckBox();
            this.GameObject_Dynamic = new System.Windows.Forms.CheckBox();
            this.GameObject_Group = new System.Windows.Forms.GroupBox();
            this.RemoveComponent = new System.Windows.Forms.Button();
            this.Transform_Group = new System.Windows.Forms.GroupBox();
            this.Transform_Scale_Input = new System.Windows.Forms.NumericUpDown();
            this.Transform_Scale_Label = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.Transform_Rotation_Z_Input = new System.Windows.Forms.NumericUpDown();
            this.label2 = new System.Windows.Forms.Label();
            this.Transform_Rotation_Y_Input = new System.Windows.Forms.NumericUpDown();
            this.label3 = new System.Windows.Forms.Label();
            this.Transform_Rotation_X_Input = new System.Windows.Forms.NumericUpDown();
            this.Transform_Rotation_Label = new System.Windows.Forms.Label();
            this.Transform_Position_Z_Label = new System.Windows.Forms.Label();
            this.Transform_Position_Z_Input = new System.Windows.Forms.NumericUpDown();
            this.Transform_Position_Y_Label = new System.Windows.Forms.Label();
            this.Transform_Position_Y_Input = new System.Windows.Forms.NumericUpDown();
            this.Transform_Position_X_Label = new System.Windows.Forms.Label();
            this.Transform_Position_X_Input = new System.Windows.Forms.NumericUpDown();
            this.Transform_Position_Label = new System.Windows.Forms.Label();
            this.Camera_Group = new System.Windows.Forms.GroupBox();
            this.Camera_FOV_Input = new System.Windows.Forms.NumericUpDown();
            this.Camera_NearPlane_Input = new System.Windows.Forms.NumericUpDown();
            this.Camera_FarPlane_Input = new System.Windows.Forms.NumericUpDown();
            this.Camera_FOV_Label = new System.Windows.Forms.Label();
            this.Camera_NearPlane_Label = new System.Windows.Forms.Label();
            this.Camera_FarPlane_Label = new System.Windows.Forms.Label();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fIleToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Lighting_Group = new System.Windows.Forms.GroupBox();
            this.Lighting_LightType_Input = new System.Windows.Forms.ComboBox();
            this.Lighting_LightType = new System.Windows.Forms.Label();
            this.Lighting_Extra_W_Label = new System.Windows.Forms.Label();
            this.Lighting_Extra_W_Input = new System.Windows.Forms.NumericUpDown();
            this.Lighting_Extra_Z_Label = new System.Windows.Forms.Label();
            this.Lighting_Extra_Z_Input = new System.Windows.Forms.NumericUpDown();
            this.Lighting_Extra_Y_Label = new System.Windows.Forms.Label();
            this.Lighting_Extra_Y_Input = new System.Windows.Forms.NumericUpDown();
            this.Lighting_Extra_X_Label = new System.Windows.Forms.Label();
            this.Lighting_Extra_X_Input = new System.Windows.Forms.NumericUpDown();
            this.Lighting_Extra_Label = new System.Windows.Forms.Label();
            this.Lighting_PickColor = new System.Windows.Forms.Button();
            this.Lighting_Color_A_Label = new System.Windows.Forms.Label();
            this.Lighting_Color_A_Input = new System.Windows.Forms.NumericUpDown();
            this.Lighting_Color_B_Label = new System.Windows.Forms.Label();
            this.Lighting_Color_B_Input = new System.Windows.Forms.NumericUpDown();
            this.Lighting_Color_G_Label = new System.Windows.Forms.Label();
            this.Lighting_Color_G_Input = new System.Windows.Forms.NumericUpDown();
            this.Lighting_Color_R_Label = new System.Windows.Forms.Label();
            this.Lighting_Color_R_Input = new System.Windows.Forms.NumericUpDown();
            this.Lighting_Color = new System.Windows.Forms.Label();
            this.LightingColorDialog = new System.Windows.Forms.ColorDialog();
            this.AudioSource_Group = new System.Windows.Forms.GroupBox();
            this.AudioSource_Browse = new System.Windows.Forms.Button();
            this.AudioSource_ClipPath = new System.Windows.Forms.TextBox();
            this.AudioSource_Clip = new System.Windows.Forms.Label();
            this.AudioSource_FileDialog = new System.Windows.Forms.OpenFileDialog();
            this.RigidBody_Group = new System.Windows.Forms.GroupBox();
            this.RigidBody_Label = new System.Windows.Forms.Label();
            this.Collider_Group = new System.Windows.Forms.GroupBox();
            this.label4 = new System.Windows.Forms.Label();
            this.Animator_Group = new System.Windows.Forms.GroupBox();
            this.Animator_Label1 = new System.Windows.Forms.Label();
            this.Animator_Animations = new System.Windows.Forms.ListBox();
            this.MeshRenderer_Group = new System.Windows.Forms.GroupBox();
            this.MeshRenderer_Mesh_Browser = new System.Windows.Forms.Button();
            this.MeshRenderer_Mesh_Input = new System.Windows.Forms.TextBox();
            this.MeshRenderer_Mesh_Label = new System.Windows.Forms.Label();
            this.SaveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.SaveAsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Animator_Default = new System.Windows.Forms.Button();
            this.Animator_Remove = new System.Windows.Forms.Button();
            this.Animator_Add = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.GameObject_ID_Input)).BeginInit();
            this.GameObject_Group.SuspendLayout();
            this.Transform_Group.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.Transform_Scale_Input)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Transform_Rotation_Z_Input)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Transform_Rotation_Y_Input)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Transform_Rotation_X_Input)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Transform_Position_Z_Input)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Transform_Position_Y_Input)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Transform_Position_X_Input)).BeginInit();
            this.Camera_Group.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.Camera_FOV_Input)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Camera_NearPlane_Input)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Camera_FarPlane_Input)).BeginInit();
            this.menuStrip1.SuspendLayout();
            this.Lighting_Group.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.Lighting_Extra_W_Input)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Lighting_Extra_Z_Input)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Lighting_Extra_Y_Input)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Lighting_Extra_X_Input)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Lighting_Color_A_Input)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Lighting_Color_B_Input)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Lighting_Color_G_Input)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Lighting_Color_R_Input)).BeginInit();
            this.AudioSource_Group.SuspendLayout();
            this.RigidBody_Group.SuspendLayout();
            this.Collider_Group.SuspendLayout();
            this.Animator_Group.SuspendLayout();
            this.MeshRenderer_Group.SuspendLayout();
            this.SuspendLayout();
            // 
            // AddComponent
            // 
            this.AddComponent.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.AddComponent.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.AddComponent.Location = new System.Drawing.Point(273, 394);
            this.AddComponent.Name = "AddComponent";
            this.AddComponent.Size = new System.Drawing.Size(117, 28);
            this.AddComponent.TabIndex = 1;
            this.AddComponent.Text = "Add Component";
            this.AddComponent.UseVisualStyleBackColor = true;
            this.AddComponent.Click += new System.EventHandler(this.AddComponent_Click);
            // 
            // ComponentList
            // 
            this.ComponentList.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.ComponentList.DropDownHeight = 115;
            this.ComponentList.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ComponentList.FormattingEnabled = true;
            this.ComponentList.IntegralHeight = false;
            this.ComponentList.Location = new System.Drawing.Point(12, 27);
            this.ComponentList.Name = "ComponentList";
            this.ComponentList.Size = new System.Drawing.Size(378, 23);
            this.ComponentList.TabIndex = 2;
            this.ComponentList.Text = "-- Select Component --";
            this.ComponentList.SelectedIndexChanged += new System.EventHandler(this.ComponentList_SelectedIndexChanged);
            // 
            // GameObject_ID_Input
            // 
            this.GameObject_ID_Input.Location = new System.Drawing.Point(69, 34);
            this.GameObject_ID_Input.Name = "GameObject_ID_Input";
            this.GameObject_ID_Input.Size = new System.Drawing.Size(126, 21);
            this.GameObject_ID_Input.TabIndex = 5;
            // 
            // GameObject_ID_Label
            // 
            this.GameObject_ID_Label.AutoSize = true;
            this.GameObject_ID_Label.Location = new System.Drawing.Point(15, 36);
            this.GameObject_ID_Label.Name = "GameObject_ID_Label";
            this.GameObject_ID_Label.Size = new System.Drawing.Size(22, 15);
            this.GameObject_ID_Label.TabIndex = 7;
            this.GameObject_ID_Label.Text = "ID:";
            // 
            // GameObject_Name_Label
            // 
            this.GameObject_Name_Label.AutoSize = true;
            this.GameObject_Name_Label.Location = new System.Drawing.Point(15, 68);
            this.GameObject_Name_Label.Name = "GameObject_Name_Label";
            this.GameObject_Name_Label.Size = new System.Drawing.Size(44, 15);
            this.GameObject_Name_Label.TabIndex = 8;
            this.GameObject_Name_Label.Text = "Name:";
            // 
            // GameObject_Name_Input
            // 
            this.GameObject_Name_Input.Location = new System.Drawing.Point(69, 65);
            this.GameObject_Name_Input.Name = "GameObject_Name_Input";
            this.GameObject_Name_Input.Size = new System.Drawing.Size(126, 21);
            this.GameObject_Name_Input.TabIndex = 9;
            this.GameObject_Name_Input.Text = "Unnamed";
            // 
            // GameObject_Tag_Label
            // 
            this.GameObject_Tag_Label.AutoSize = true;
            this.GameObject_Tag_Label.Location = new System.Drawing.Point(15, 99);
            this.GameObject_Tag_Label.Name = "GameObject_Tag_Label";
            this.GameObject_Tag_Label.Size = new System.Drawing.Size(31, 15);
            this.GameObject_Tag_Label.TabIndex = 10;
            this.GameObject_Tag_Label.Text = "Tag:";
            // 
            // GameObject_Tag_Input
            // 
            this.GameObject_Tag_Input.Location = new System.Drawing.Point(69, 96);
            this.GameObject_Tag_Input.Name = "GameObject_Tag_Input";
            this.GameObject_Tag_Input.Size = new System.Drawing.Size(126, 21);
            this.GameObject_Tag_Input.TabIndex = 11;
            this.GameObject_Tag_Input.Text = "Untagged";
            // 
            // GameObject_Transperent
            // 
            this.GameObject_Transperent.AutoSize = true;
            this.GameObject_Transperent.Location = new System.Drawing.Point(18, 136);
            this.GameObject_Transperent.Name = "GameObject_Transperent";
            this.GameObject_Transperent.Size = new System.Drawing.Size(92, 19);
            this.GameObject_Transperent.TabIndex = 12;
            this.GameObject_Transperent.Text = "Transparent";
            this.GameObject_Transperent.UseVisualStyleBackColor = true;
            // 
            // GameObject_Dynamic
            // 
            this.GameObject_Dynamic.AutoSize = true;
            this.GameObject_Dynamic.Location = new System.Drawing.Point(18, 161);
            this.GameObject_Dynamic.Name = "GameObject_Dynamic";
            this.GameObject_Dynamic.Size = new System.Drawing.Size(74, 19);
            this.GameObject_Dynamic.TabIndex = 13;
            this.GameObject_Dynamic.Text = "Dynamic";
            this.GameObject_Dynamic.UseVisualStyleBackColor = true;
            // 
            // GameObject_Group
            // 
            this.GameObject_Group.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.GameObject_Group.Controls.Add(this.GameObject_Tag_Input);
            this.GameObject_Group.Controls.Add(this.GameObject_Dynamic);
            this.GameObject_Group.Controls.Add(this.GameObject_Transperent);
            this.GameObject_Group.Controls.Add(this.GameObject_ID_Input);
            this.GameObject_Group.Controls.Add(this.GameObject_ID_Label);
            this.GameObject_Group.Controls.Add(this.GameObject_Tag_Label);
            this.GameObject_Group.Controls.Add(this.GameObject_Name_Label);
            this.GameObject_Group.Controls.Add(this.GameObject_Name_Input);
            this.GameObject_Group.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.GameObject_Group.Location = new System.Drawing.Point(12, 69);
            this.GameObject_Group.Name = "GameObject_Group";
            this.GameObject_Group.Size = new System.Drawing.Size(378, 197);
            this.GameObject_Group.TabIndex = 14;
            this.GameObject_Group.TabStop = false;
            this.GameObject_Group.Text = "GameObject";
            this.GameObject_Group.Visible = false;
            // 
            // RemoveComponent
            // 
            this.RemoveComponent.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.RemoveComponent.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.RemoveComponent.Location = new System.Drawing.Point(132, 394);
            this.RemoveComponent.Name = "RemoveComponent";
            this.RemoveComponent.Size = new System.Drawing.Size(135, 28);
            this.RemoveComponent.TabIndex = 15;
            this.RemoveComponent.Text = "Remove Component";
            this.RemoveComponent.UseVisualStyleBackColor = true;
            this.RemoveComponent.Click += new System.EventHandler(this.RemoveComponent_Click);
            // 
            // Transform_Group
            // 
            this.Transform_Group.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.Transform_Group.Controls.Add(this.Transform_Scale_Input);
            this.Transform_Group.Controls.Add(this.Transform_Scale_Label);
            this.Transform_Group.Controls.Add(this.label1);
            this.Transform_Group.Controls.Add(this.Transform_Rotation_Z_Input);
            this.Transform_Group.Controls.Add(this.label2);
            this.Transform_Group.Controls.Add(this.Transform_Rotation_Y_Input);
            this.Transform_Group.Controls.Add(this.label3);
            this.Transform_Group.Controls.Add(this.Transform_Rotation_X_Input);
            this.Transform_Group.Controls.Add(this.Transform_Rotation_Label);
            this.Transform_Group.Controls.Add(this.Transform_Position_Z_Label);
            this.Transform_Group.Controls.Add(this.Transform_Position_Z_Input);
            this.Transform_Group.Controls.Add(this.Transform_Position_Y_Label);
            this.Transform_Group.Controls.Add(this.Transform_Position_Y_Input);
            this.Transform_Group.Controls.Add(this.Transform_Position_X_Label);
            this.Transform_Group.Controls.Add(this.Transform_Position_X_Input);
            this.Transform_Group.Controls.Add(this.Transform_Position_Label);
            this.Transform_Group.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Transform_Group.Location = new System.Drawing.Point(12, 69);
            this.Transform_Group.Name = "Transform_Group";
            this.Transform_Group.Size = new System.Drawing.Size(378, 287);
            this.Transform_Group.TabIndex = 15;
            this.Transform_Group.TabStop = false;
            this.Transform_Group.Text = "Transform";
            this.Transform_Group.Visible = false;
            // 
            // Transform_Scale_Input
            // 
            this.Transform_Scale_Input.DecimalPlaces = 4;
            this.Transform_Scale_Input.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.Transform_Scale_Input.Location = new System.Drawing.Point(62, 247);
            this.Transform_Scale_Input.Maximum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.Transform_Scale_Input.Name = "Transform_Scale_Input";
            this.Transform_Scale_Input.Size = new System.Drawing.Size(82, 21);
            this.Transform_Scale_Input.TabIndex = 28;
            // 
            // Transform_Scale_Label
            // 
            this.Transform_Scale_Label.AutoSize = true;
            this.Transform_Scale_Label.Location = new System.Drawing.Point(15, 250);
            this.Transform_Scale_Label.Name = "Transform_Scale_Label";
            this.Transform_Scale_Label.Size = new System.Drawing.Size(41, 15);
            this.Transform_Scale_Label.TabIndex = 27;
            this.Transform_Scale_Label.Text = "Scale:";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(29, 212);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(14, 15);
            this.label1.TabIndex = 26;
            this.label1.Text = "Z";
            // 
            // Transform_Rotation_Z_Input
            // 
            this.Transform_Rotation_Z_Input.DecimalPlaces = 4;
            this.Transform_Rotation_Z_Input.Location = new System.Drawing.Point(47, 209);
            this.Transform_Rotation_Z_Input.Maximum = new decimal(new int[] {
            -1,
            -1,
            -1,
            0});
            this.Transform_Rotation_Z_Input.Minimum = new decimal(new int[] {
            -1,
            -1,
            -1,
            -2147483648});
            this.Transform_Rotation_Z_Input.Name = "Transform_Rotation_Z_Input";
            this.Transform_Rotation_Z_Input.Size = new System.Drawing.Size(82, 21);
            this.Transform_Rotation_Z_Input.TabIndex = 25;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(29, 185);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(14, 15);
            this.label2.TabIndex = 24;
            this.label2.Text = "Y";
            // 
            // Transform_Rotation_Y_Input
            // 
            this.Transform_Rotation_Y_Input.DecimalPlaces = 4;
            this.Transform_Rotation_Y_Input.Location = new System.Drawing.Point(47, 182);
            this.Transform_Rotation_Y_Input.Maximum = new decimal(new int[] {
            -1,
            -1,
            -1,
            0});
            this.Transform_Rotation_Y_Input.Minimum = new decimal(new int[] {
            -1,
            -1,
            -1,
            -2147483648});
            this.Transform_Rotation_Y_Input.Name = "Transform_Rotation_Y_Input";
            this.Transform_Rotation_Y_Input.Size = new System.Drawing.Size(82, 21);
            this.Transform_Rotation_Y_Input.TabIndex = 23;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(29, 158);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(15, 15);
            this.label3.TabIndex = 22;
            this.label3.Text = "X";
            // 
            // Transform_Rotation_X_Input
            // 
            this.Transform_Rotation_X_Input.DecimalPlaces = 4;
            this.Transform_Rotation_X_Input.Location = new System.Drawing.Point(47, 155);
            this.Transform_Rotation_X_Input.Maximum = new decimal(new int[] {
            -1,
            -1,
            -1,
            0});
            this.Transform_Rotation_X_Input.Minimum = new decimal(new int[] {
            -1,
            -1,
            -1,
            -2147483648});
            this.Transform_Rotation_X_Input.Name = "Transform_Rotation_X_Input";
            this.Transform_Rotation_X_Input.Size = new System.Drawing.Size(82, 21);
            this.Transform_Rotation_X_Input.TabIndex = 21;
            // 
            // Transform_Rotation_Label
            // 
            this.Transform_Rotation_Label.AutoSize = true;
            this.Transform_Rotation_Label.Location = new System.Drawing.Point(15, 136);
            this.Transform_Rotation_Label.Name = "Transform_Rotation_Label";
            this.Transform_Rotation_Label.Size = new System.Drawing.Size(56, 15);
            this.Transform_Rotation_Label.TabIndex = 20;
            this.Transform_Rotation_Label.Text = "Rotation:";
            // 
            // Transform_Position_Z_Label
            // 
            this.Transform_Position_Z_Label.AutoSize = true;
            this.Transform_Position_Z_Label.Location = new System.Drawing.Point(29, 103);
            this.Transform_Position_Z_Label.Name = "Transform_Position_Z_Label";
            this.Transform_Position_Z_Label.Size = new System.Drawing.Size(14, 15);
            this.Transform_Position_Z_Label.TabIndex = 19;
            this.Transform_Position_Z_Label.Text = "Z";
            // 
            // Transform_Position_Z_Input
            // 
            this.Transform_Position_Z_Input.DecimalPlaces = 4;
            this.Transform_Position_Z_Input.Location = new System.Drawing.Point(47, 100);
            this.Transform_Position_Z_Input.Maximum = new decimal(new int[] {
            -1,
            -1,
            -1,
            0});
            this.Transform_Position_Z_Input.Minimum = new decimal(new int[] {
            -1,
            -1,
            -1,
            -2147483648});
            this.Transform_Position_Z_Input.Name = "Transform_Position_Z_Input";
            this.Transform_Position_Z_Input.Size = new System.Drawing.Size(82, 21);
            this.Transform_Position_Z_Input.TabIndex = 18;
            // 
            // Transform_Position_Y_Label
            // 
            this.Transform_Position_Y_Label.AutoSize = true;
            this.Transform_Position_Y_Label.Location = new System.Drawing.Point(29, 76);
            this.Transform_Position_Y_Label.Name = "Transform_Position_Y_Label";
            this.Transform_Position_Y_Label.Size = new System.Drawing.Size(14, 15);
            this.Transform_Position_Y_Label.TabIndex = 17;
            this.Transform_Position_Y_Label.Text = "Y";
            // 
            // Transform_Position_Y_Input
            // 
            this.Transform_Position_Y_Input.DecimalPlaces = 4;
            this.Transform_Position_Y_Input.Location = new System.Drawing.Point(47, 73);
            this.Transform_Position_Y_Input.Maximum = new decimal(new int[] {
            -1,
            -1,
            -1,
            0});
            this.Transform_Position_Y_Input.Minimum = new decimal(new int[] {
            -1,
            -1,
            -1,
            -2147483648});
            this.Transform_Position_Y_Input.Name = "Transform_Position_Y_Input";
            this.Transform_Position_Y_Input.Size = new System.Drawing.Size(82, 21);
            this.Transform_Position_Y_Input.TabIndex = 16;
            // 
            // Transform_Position_X_Label
            // 
            this.Transform_Position_X_Label.AutoSize = true;
            this.Transform_Position_X_Label.Location = new System.Drawing.Point(29, 49);
            this.Transform_Position_X_Label.Name = "Transform_Position_X_Label";
            this.Transform_Position_X_Label.Size = new System.Drawing.Size(15, 15);
            this.Transform_Position_X_Label.TabIndex = 15;
            this.Transform_Position_X_Label.Text = "X";
            // 
            // Transform_Position_X_Input
            // 
            this.Transform_Position_X_Input.DecimalPlaces = 4;
            this.Transform_Position_X_Input.Location = new System.Drawing.Point(47, 46);
            this.Transform_Position_X_Input.Maximum = new decimal(new int[] {
            -1,
            -1,
            -1,
            0});
            this.Transform_Position_X_Input.Minimum = new decimal(new int[] {
            -1,
            -1,
            -1,
            -2147483648});
            this.Transform_Position_X_Input.Name = "Transform_Position_X_Input";
            this.Transform_Position_X_Input.Size = new System.Drawing.Size(82, 21);
            this.Transform_Position_X_Input.TabIndex = 14;
            // 
            // Transform_Position_Label
            // 
            this.Transform_Position_Label.AutoSize = true;
            this.Transform_Position_Label.Location = new System.Drawing.Point(15, 27);
            this.Transform_Position_Label.Name = "Transform_Position_Label";
            this.Transform_Position_Label.Size = new System.Drawing.Size(54, 15);
            this.Transform_Position_Label.TabIndex = 7;
            this.Transform_Position_Label.Text = "Position:";
            // 
            // Camera_Group
            // 
            this.Camera_Group.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.Camera_Group.Controls.Add(this.Camera_FOV_Input);
            this.Camera_Group.Controls.Add(this.Camera_NearPlane_Input);
            this.Camera_Group.Controls.Add(this.Camera_FarPlane_Input);
            this.Camera_Group.Controls.Add(this.Camera_FOV_Label);
            this.Camera_Group.Controls.Add(this.Camera_NearPlane_Label);
            this.Camera_Group.Controls.Add(this.Camera_FarPlane_Label);
            this.Camera_Group.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Camera_Group.Location = new System.Drawing.Point(12, 69);
            this.Camera_Group.Name = "Camera_Group";
            this.Camera_Group.Size = new System.Drawing.Size(378, 133);
            this.Camera_Group.TabIndex = 29;
            this.Camera_Group.TabStop = false;
            this.Camera_Group.Text = "Camera";
            this.Camera_Group.Visible = false;
            // 
            // Camera_FOV_Input
            // 
            this.Camera_FOV_Input.DecimalPlaces = 4;
            this.Camera_FOV_Input.Location = new System.Drawing.Point(113, 91);
            this.Camera_FOV_Input.Maximum = new decimal(new int[] {
            -1,
            -1,
            -1,
            0});
            this.Camera_FOV_Input.Minimum = new decimal(new int[] {
            -1,
            -1,
            -1,
            -2147483648});
            this.Camera_FOV_Input.Name = "Camera_FOV_Input";
            this.Camera_FOV_Input.Size = new System.Drawing.Size(82, 21);
            this.Camera_FOV_Input.TabIndex = 32;
            // 
            // Camera_NearPlane_Input
            // 
            this.Camera_NearPlane_Input.DecimalPlaces = 4;
            this.Camera_NearPlane_Input.Location = new System.Drawing.Point(113, 59);
            this.Camera_NearPlane_Input.Maximum = new decimal(new int[] {
            -1,
            -1,
            -1,
            0});
            this.Camera_NearPlane_Input.Minimum = new decimal(new int[] {
            -1,
            -1,
            -1,
            -2147483648});
            this.Camera_NearPlane_Input.Name = "Camera_NearPlane_Input";
            this.Camera_NearPlane_Input.Size = new System.Drawing.Size(82, 21);
            this.Camera_NearPlane_Input.TabIndex = 31;
            // 
            // Camera_FarPlane_Input
            // 
            this.Camera_FarPlane_Input.DecimalPlaces = 4;
            this.Camera_FarPlane_Input.Location = new System.Drawing.Point(113, 26);
            this.Camera_FarPlane_Input.Maximum = new decimal(new int[] {
            -1,
            -1,
            -1,
            0});
            this.Camera_FarPlane_Input.Minimum = new decimal(new int[] {
            -1,
            -1,
            -1,
            -2147483648});
            this.Camera_FarPlane_Input.Name = "Camera_FarPlane_Input";
            this.Camera_FarPlane_Input.Size = new System.Drawing.Size(82, 21);
            this.Camera_FarPlane_Input.TabIndex = 30;
            // 
            // Camera_FOV_Label
            // 
            this.Camera_FOV_Label.AutoSize = true;
            this.Camera_FOV_Label.Location = new System.Drawing.Point(15, 94);
            this.Camera_FOV_Label.Name = "Camera_FOV_Label";
            this.Camera_FOV_Label.Size = new System.Drawing.Size(33, 15);
            this.Camera_FOV_Label.TabIndex = 3;
            this.Camera_FOV_Label.Text = "FOV:";
            // 
            // Camera_NearPlane_Label
            // 
            this.Camera_NearPlane_Label.AutoSize = true;
            this.Camera_NearPlane_Label.Location = new System.Drawing.Point(15, 61);
            this.Camera_NearPlane_Label.Name = "Camera_NearPlane_Label";
            this.Camera_NearPlane_Label.Size = new System.Drawing.Size(72, 15);
            this.Camera_NearPlane_Label.TabIndex = 2;
            this.Camera_NearPlane_Label.Text = "Near Plane:";
            // 
            // Camera_FarPlane_Label
            // 
            this.Camera_FarPlane_Label.AutoSize = true;
            this.Camera_FarPlane_Label.Location = new System.Drawing.Point(15, 28);
            this.Camera_FarPlane_Label.Name = "Camera_FarPlane_Label";
            this.Camera_FarPlane_Label.Size = new System.Drawing.Size(63, 15);
            this.Camera_FarPlane_Label.TabIndex = 1;
            this.Camera_FarPlane_Label.Text = "Far Plane:";
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fIleToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(402, 24);
            this.menuStrip1.TabIndex = 16;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fIleToolStripMenuItem
            // 
            this.fIleToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.SaveToolStripMenuItem,
            this.SaveAsToolStripMenuItem});
            this.fIleToolStripMenuItem.Name = "fIleToolStripMenuItem";
            this.fIleToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fIleToolStripMenuItem.Text = "File";
            // 
            // Lighting_Group
            // 
            this.Lighting_Group.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.Lighting_Group.Controls.Add(this.Lighting_LightType_Input);
            this.Lighting_Group.Controls.Add(this.Lighting_LightType);
            this.Lighting_Group.Controls.Add(this.Lighting_Extra_W_Label);
            this.Lighting_Group.Controls.Add(this.Lighting_Extra_W_Input);
            this.Lighting_Group.Controls.Add(this.Lighting_Extra_Z_Label);
            this.Lighting_Group.Controls.Add(this.Lighting_Extra_Z_Input);
            this.Lighting_Group.Controls.Add(this.Lighting_Extra_Y_Label);
            this.Lighting_Group.Controls.Add(this.Lighting_Extra_Y_Input);
            this.Lighting_Group.Controls.Add(this.Lighting_Extra_X_Label);
            this.Lighting_Group.Controls.Add(this.Lighting_Extra_X_Input);
            this.Lighting_Group.Controls.Add(this.Lighting_Extra_Label);
            this.Lighting_Group.Controls.Add(this.Lighting_PickColor);
            this.Lighting_Group.Controls.Add(this.Lighting_Color_A_Label);
            this.Lighting_Group.Controls.Add(this.Lighting_Color_A_Input);
            this.Lighting_Group.Controls.Add(this.Lighting_Color_B_Label);
            this.Lighting_Group.Controls.Add(this.Lighting_Color_B_Input);
            this.Lighting_Group.Controls.Add(this.Lighting_Color_G_Label);
            this.Lighting_Group.Controls.Add(this.Lighting_Color_G_Input);
            this.Lighting_Group.Controls.Add(this.Lighting_Color_R_Label);
            this.Lighting_Group.Controls.Add(this.Lighting_Color_R_Input);
            this.Lighting_Group.Controls.Add(this.Lighting_Color);
            this.Lighting_Group.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Lighting_Group.Location = new System.Drawing.Point(12, 69);
            this.Lighting_Group.Name = "Lighting_Group";
            this.Lighting_Group.Size = new System.Drawing.Size(378, 319);
            this.Lighting_Group.TabIndex = 29;
            this.Lighting_Group.TabStop = false;
            this.Lighting_Group.Text = "Lighting";
            this.Lighting_Group.Visible = false;
            // 
            // Lighting_LightType_Input
            // 
            this.Lighting_LightType_Input.FormattingEnabled = true;
            this.Lighting_LightType_Input.Items.AddRange(new object[] {
            "None",
            "Ambient",
            "Directional",
            "Point",
            "Spot"});
            this.Lighting_LightType_Input.Location = new System.Drawing.Point(18, 203);
            this.Lighting_LightType_Input.Name = "Lighting_LightType_Input";
            this.Lighting_LightType_Input.Size = new System.Drawing.Size(329, 23);
            this.Lighting_LightType_Input.TabIndex = 30;
            this.Lighting_LightType_Input.Text = "-- Select Light Type --";
            // 
            // Lighting_LightType
            // 
            this.Lighting_LightType.AutoSize = true;
            this.Lighting_LightType.Location = new System.Drawing.Point(15, 182);
            this.Lighting_LightType.Name = "Lighting_LightType";
            this.Lighting_LightType.Size = new System.Drawing.Size(63, 15);
            this.Lighting_LightType.TabIndex = 41;
            this.Lighting_LightType.Text = "Light Type";
            // 
            // Lighting_Extra_W_Label
            // 
            this.Lighting_Extra_W_Label.AutoSize = true;
            this.Lighting_Extra_W_Label.Location = new System.Drawing.Point(269, 142);
            this.Lighting_Extra_W_Label.Name = "Lighting_Extra_W_Label";
            this.Lighting_Extra_W_Label.Size = new System.Drawing.Size(18, 15);
            this.Lighting_Extra_W_Label.TabIndex = 40;
            this.Lighting_Extra_W_Label.Text = "W";
            // 
            // Lighting_Extra_W_Input
            // 
            this.Lighting_Extra_W_Input.DecimalPlaces = 1;
            this.Lighting_Extra_W_Input.Location = new System.Drawing.Point(287, 139);
            this.Lighting_Extra_W_Input.Maximum = new decimal(new int[] {
            -1,
            -1,
            -1,
            0});
            this.Lighting_Extra_W_Input.Name = "Lighting_Extra_W_Input";
            this.Lighting_Extra_W_Input.Size = new System.Drawing.Size(60, 21);
            this.Lighting_Extra_W_Input.TabIndex = 39;
            // 
            // Lighting_Extra_Z_Label
            // 
            this.Lighting_Extra_Z_Label.AutoSize = true;
            this.Lighting_Extra_Z_Label.Location = new System.Drawing.Point(189, 142);
            this.Lighting_Extra_Z_Label.Name = "Lighting_Extra_Z_Label";
            this.Lighting_Extra_Z_Label.Size = new System.Drawing.Size(14, 15);
            this.Lighting_Extra_Z_Label.TabIndex = 38;
            this.Lighting_Extra_Z_Label.Text = "Z";
            // 
            // Lighting_Extra_Z_Input
            // 
            this.Lighting_Extra_Z_Input.DecimalPlaces = 1;
            this.Lighting_Extra_Z_Input.Location = new System.Drawing.Point(207, 139);
            this.Lighting_Extra_Z_Input.Maximum = new decimal(new int[] {
            -1,
            -1,
            -1,
            0});
            this.Lighting_Extra_Z_Input.Name = "Lighting_Extra_Z_Input";
            this.Lighting_Extra_Z_Input.Size = new System.Drawing.Size(60, 21);
            this.Lighting_Extra_Z_Input.TabIndex = 37;
            // 
            // Lighting_Extra_Y_Label
            // 
            this.Lighting_Extra_Y_Label.AutoSize = true;
            this.Lighting_Extra_Y_Label.Location = new System.Drawing.Point(109, 142);
            this.Lighting_Extra_Y_Label.Name = "Lighting_Extra_Y_Label";
            this.Lighting_Extra_Y_Label.Size = new System.Drawing.Size(14, 15);
            this.Lighting_Extra_Y_Label.TabIndex = 36;
            this.Lighting_Extra_Y_Label.Text = "Y";
            // 
            // Lighting_Extra_Y_Input
            // 
            this.Lighting_Extra_Y_Input.DecimalPlaces = 1;
            this.Lighting_Extra_Y_Input.Location = new System.Drawing.Point(127, 139);
            this.Lighting_Extra_Y_Input.Maximum = new decimal(new int[] {
            -1,
            -1,
            -1,
            0});
            this.Lighting_Extra_Y_Input.Name = "Lighting_Extra_Y_Input";
            this.Lighting_Extra_Y_Input.Size = new System.Drawing.Size(60, 21);
            this.Lighting_Extra_Y_Input.TabIndex = 35;
            // 
            // Lighting_Extra_X_Label
            // 
            this.Lighting_Extra_X_Label.AutoSize = true;
            this.Lighting_Extra_X_Label.Location = new System.Drawing.Point(29, 142);
            this.Lighting_Extra_X_Label.Name = "Lighting_Extra_X_Label";
            this.Lighting_Extra_X_Label.Size = new System.Drawing.Size(15, 15);
            this.Lighting_Extra_X_Label.TabIndex = 34;
            this.Lighting_Extra_X_Label.Text = "X";
            // 
            // Lighting_Extra_X_Input
            // 
            this.Lighting_Extra_X_Input.DecimalPlaces = 1;
            this.Lighting_Extra_X_Input.Location = new System.Drawing.Point(47, 139);
            this.Lighting_Extra_X_Input.Maximum = new decimal(new int[] {
            -1,
            -1,
            -1,
            0});
            this.Lighting_Extra_X_Input.Name = "Lighting_Extra_X_Input";
            this.Lighting_Extra_X_Input.Size = new System.Drawing.Size(60, 21);
            this.Lighting_Extra_X_Input.TabIndex = 33;
            // 
            // Lighting_Extra_Label
            // 
            this.Lighting_Extra_Label.AutoSize = true;
            this.Lighting_Extra_Label.Location = new System.Drawing.Point(15, 118);
            this.Lighting_Extra_Label.Name = "Lighting_Extra_Label";
            this.Lighting_Extra_Label.Size = new System.Drawing.Size(38, 15);
            this.Lighting_Extra_Label.TabIndex = 32;
            this.Lighting_Extra_Label.Text = "Extra:";
            // 
            // Lighting_PickColor
            // 
            this.Lighting_PickColor.Location = new System.Drawing.Point(32, 79);
            this.Lighting_PickColor.Name = "Lighting_PickColor";
            this.Lighting_PickColor.Size = new System.Drawing.Size(93, 25);
            this.Lighting_PickColor.TabIndex = 31;
            this.Lighting_PickColor.Text = "Pick Color";
            this.Lighting_PickColor.UseVisualStyleBackColor = true;
            this.Lighting_PickColor.Click += new System.EventHandler(this.Lighting_PickColor_Click);
            // 
            // Lighting_Color_A_Label
            // 
            this.Lighting_Color_A_Label.AutoSize = true;
            this.Lighting_Color_A_Label.Location = new System.Drawing.Point(269, 52);
            this.Lighting_Color_A_Label.Name = "Lighting_Color_A_Label";
            this.Lighting_Color_A_Label.Size = new System.Drawing.Size(14, 15);
            this.Lighting_Color_A_Label.TabIndex = 30;
            this.Lighting_Color_A_Label.Text = "A";
            // 
            // Lighting_Color_A_Input
            // 
            this.Lighting_Color_A_Input.DecimalPlaces = 1;
            this.Lighting_Color_A_Input.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.Lighting_Color_A_Input.Location = new System.Drawing.Point(287, 49);
            this.Lighting_Color_A_Input.Maximum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.Lighting_Color_A_Input.Name = "Lighting_Color_A_Input";
            this.Lighting_Color_A_Input.Size = new System.Drawing.Size(60, 21);
            this.Lighting_Color_A_Input.TabIndex = 29;
            this.Lighting_Color_A_Input.Value = new decimal(new int[] {
            10,
            0,
            0,
            65536});
            // 
            // Lighting_Color_B_Label
            // 
            this.Lighting_Color_B_Label.AutoSize = true;
            this.Lighting_Color_B_Label.Location = new System.Drawing.Point(189, 52);
            this.Lighting_Color_B_Label.Name = "Lighting_Color_B_Label";
            this.Lighting_Color_B_Label.Size = new System.Drawing.Size(15, 15);
            this.Lighting_Color_B_Label.TabIndex = 19;
            this.Lighting_Color_B_Label.Text = "B";
            // 
            // Lighting_Color_B_Input
            // 
            this.Lighting_Color_B_Input.Location = new System.Drawing.Point(207, 49);
            this.Lighting_Color_B_Input.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.Lighting_Color_B_Input.Name = "Lighting_Color_B_Input";
            this.Lighting_Color_B_Input.Size = new System.Drawing.Size(60, 21);
            this.Lighting_Color_B_Input.TabIndex = 18;
            this.Lighting_Color_B_Input.Value = new decimal(new int[] {
            255,
            0,
            0,
            0});
            // 
            // Lighting_Color_G_Label
            // 
            this.Lighting_Color_G_Label.AutoSize = true;
            this.Lighting_Color_G_Label.Location = new System.Drawing.Point(109, 52);
            this.Lighting_Color_G_Label.Name = "Lighting_Color_G_Label";
            this.Lighting_Color_G_Label.Size = new System.Drawing.Size(16, 15);
            this.Lighting_Color_G_Label.TabIndex = 17;
            this.Lighting_Color_G_Label.Text = "G";
            // 
            // Lighting_Color_G_Input
            // 
            this.Lighting_Color_G_Input.Location = new System.Drawing.Point(127, 49);
            this.Lighting_Color_G_Input.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.Lighting_Color_G_Input.Name = "Lighting_Color_G_Input";
            this.Lighting_Color_G_Input.Size = new System.Drawing.Size(60, 21);
            this.Lighting_Color_G_Input.TabIndex = 16;
            this.Lighting_Color_G_Input.Value = new decimal(new int[] {
            255,
            0,
            0,
            0});
            // 
            // Lighting_Color_R_Label
            // 
            this.Lighting_Color_R_Label.AutoSize = true;
            this.Lighting_Color_R_Label.Location = new System.Drawing.Point(29, 52);
            this.Lighting_Color_R_Label.Name = "Lighting_Color_R_Label";
            this.Lighting_Color_R_Label.Size = new System.Drawing.Size(16, 15);
            this.Lighting_Color_R_Label.TabIndex = 15;
            this.Lighting_Color_R_Label.Text = "R";
            // 
            // Lighting_Color_R_Input
            // 
            this.Lighting_Color_R_Input.Location = new System.Drawing.Point(47, 49);
            this.Lighting_Color_R_Input.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.Lighting_Color_R_Input.Name = "Lighting_Color_R_Input";
            this.Lighting_Color_R_Input.Size = new System.Drawing.Size(60, 21);
            this.Lighting_Color_R_Input.TabIndex = 14;
            this.Lighting_Color_R_Input.Value = new decimal(new int[] {
            255,
            0,
            0,
            0});
            // 
            // Lighting_Color
            // 
            this.Lighting_Color.AutoSize = true;
            this.Lighting_Color.Location = new System.Drawing.Point(15, 27);
            this.Lighting_Color.Name = "Lighting_Color";
            this.Lighting_Color.Size = new System.Drawing.Size(39, 15);
            this.Lighting_Color.TabIndex = 7;
            this.Lighting_Color.Text = "Color:";
            // 
            // LightingColorDialog
            // 
            this.LightingColorDialog.Color = System.Drawing.Color.White;
            // 
            // AudioSource_Group
            // 
            this.AudioSource_Group.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.AudioSource_Group.Controls.Add(this.AudioSource_Browse);
            this.AudioSource_Group.Controls.Add(this.AudioSource_ClipPath);
            this.AudioSource_Group.Controls.Add(this.AudioSource_Clip);
            this.AudioSource_Group.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.AudioSource_Group.Location = new System.Drawing.Point(12, 69);
            this.AudioSource_Group.Name = "AudioSource_Group";
            this.AudioSource_Group.Size = new System.Drawing.Size(378, 133);
            this.AudioSource_Group.TabIndex = 33;
            this.AudioSource_Group.TabStop = false;
            this.AudioSource_Group.Text = "AudioSource";
            this.AudioSource_Group.Visible = false;
            // 
            // AudioSource_Browse
            // 
            this.AudioSource_Browse.Location = new System.Drawing.Point(192, 76);
            this.AudioSource_Browse.Name = "AudioSource_Browse";
            this.AudioSource_Browse.Size = new System.Drawing.Size(75, 23);
            this.AudioSource_Browse.TabIndex = 3;
            this.AudioSource_Browse.Text = "Browse...";
            this.AudioSource_Browse.UseVisualStyleBackColor = true;
            this.AudioSource_Browse.Click += new System.EventHandler(this.AudioSource_Browse_Click);
            // 
            // AudioSource_ClipPath
            // 
            this.AudioSource_ClipPath.Location = new System.Drawing.Point(18, 49);
            this.AudioSource_ClipPath.Name = "AudioSource_ClipPath";
            this.AudioSource_ClipPath.Size = new System.Drawing.Size(249, 21);
            this.AudioSource_ClipPath.TabIndex = 2;
            // 
            // AudioSource_Clip
            // 
            this.AudioSource_Clip.AutoSize = true;
            this.AudioSource_Clip.Location = new System.Drawing.Point(15, 28);
            this.AudioSource_Clip.Name = "AudioSource_Clip";
            this.AudioSource_Clip.Size = new System.Drawing.Size(31, 15);
            this.AudioSource_Clip.TabIndex = 1;
            this.AudioSource_Clip.Text = "Clip:";
            // 
            // RigidBody_Group
            // 
            this.RigidBody_Group.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.RigidBody_Group.Controls.Add(this.RigidBody_Label);
            this.RigidBody_Group.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.RigidBody_Group.Location = new System.Drawing.Point(12, 69);
            this.RigidBody_Group.Name = "RigidBody_Group";
            this.RigidBody_Group.Size = new System.Drawing.Size(378, 94);
            this.RigidBody_Group.TabIndex = 15;
            this.RigidBody_Group.TabStop = false;
            this.RigidBody_Group.Text = "RigidBody";
            this.RigidBody_Group.Visible = false;
            // 
            // RigidBody_Label
            // 
            this.RigidBody_Label.AutoSize = true;
            this.RigidBody_Label.Location = new System.Drawing.Point(15, 26);
            this.RigidBody_Label.Name = "RigidBody_Label";
            this.RigidBody_Label.Size = new System.Drawing.Size(69, 15);
            this.RigidBody_Label.TabIndex = 0;
            this.RigidBody_Label.Text = "No content.";
            // 
            // Collider_Group
            // 
            this.Collider_Group.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.Collider_Group.Controls.Add(this.label4);
            this.Collider_Group.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Collider_Group.Location = new System.Drawing.Point(12, 69);
            this.Collider_Group.Name = "Collider_Group";
            this.Collider_Group.Size = new System.Drawing.Size(378, 94);
            this.Collider_Group.TabIndex = 16;
            this.Collider_Group.TabStop = false;
            this.Collider_Group.Text = "Collider";
            this.Collider_Group.Visible = false;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(15, 26);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(69, 15);
            this.label4.TabIndex = 0;
            this.label4.Text = "No content.";
            // 
            // Animator_Group
            // 
            this.Animator_Group.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.Animator_Group.Controls.Add(this.Animator_Default);
            this.Animator_Group.Controls.Add(this.Animator_Label1);
            this.Animator_Group.Controls.Add(this.Animator_Remove);
            this.Animator_Group.Controls.Add(this.Animator_Add);
            this.Animator_Group.Controls.Add(this.Animator_Animations);
            this.Animator_Group.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Animator_Group.Location = new System.Drawing.Point(12, 69);
            this.Animator_Group.Name = "Animator_Group";
            this.Animator_Group.Size = new System.Drawing.Size(378, 173);
            this.Animator_Group.TabIndex = 29;
            this.Animator_Group.TabStop = false;
            this.Animator_Group.Text = "Animator";
            this.Animator_Group.Visible = false;
            // 
            // Animator_Label1
            // 
            this.Animator_Label1.AutoSize = true;
            this.Animator_Label1.Location = new System.Drawing.Point(3, 26);
            this.Animator_Label1.Name = "Animator_Label1";
            this.Animator_Label1.Size = new System.Drawing.Size(71, 15);
            this.Animator_Label1.TabIndex = 3;
            this.Animator_Label1.Text = "Animations:";
            // 
            // Animator_Animations
            // 
            this.Animator_Animations.FormattingEnabled = true;
            this.Animator_Animations.ItemHeight = 15;
            this.Animator_Animations.Location = new System.Drawing.Point(6, 44);
            this.Animator_Animations.Name = "Animator_Animations";
            this.Animator_Animations.Size = new System.Drawing.Size(363, 94);
            this.Animator_Animations.TabIndex = 0;
            // 
            // MeshRenderer_Group
            // 
            this.MeshRenderer_Group.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.MeshRenderer_Group.Controls.Add(this.MeshRenderer_Mesh_Browser);
            this.MeshRenderer_Group.Controls.Add(this.MeshRenderer_Mesh_Input);
            this.MeshRenderer_Group.Controls.Add(this.MeshRenderer_Mesh_Label);
            this.MeshRenderer_Group.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.MeshRenderer_Group.Location = new System.Drawing.Point(12, 69);
            this.MeshRenderer_Group.Name = "MeshRenderer_Group";
            this.MeshRenderer_Group.Size = new System.Drawing.Size(378, 94);
            this.MeshRenderer_Group.TabIndex = 17;
            this.MeshRenderer_Group.TabStop = false;
            this.MeshRenderer_Group.Text = "MeshRenderer";
            this.MeshRenderer_Group.Visible = false;
            // 
            // MeshRenderer_Mesh_Browser
            // 
            this.MeshRenderer_Mesh_Browser.Location = new System.Drawing.Point(195, 30);
            this.MeshRenderer_Mesh_Browser.Name = "MeshRenderer_Mesh_Browser";
            this.MeshRenderer_Mesh_Browser.Size = new System.Drawing.Size(31, 23);
            this.MeshRenderer_Mesh_Browser.TabIndex = 2;
            this.MeshRenderer_Mesh_Browser.Text = "...";
            this.MeshRenderer_Mesh_Browser.UseVisualStyleBackColor = true;
            this.MeshRenderer_Mesh_Browser.Click += new System.EventHandler(this.MeshRenderer_Mesh_Browser_Click);
            // 
            // MeshRenderer_Mesh_Input
            // 
            this.MeshRenderer_Mesh_Input.Location = new System.Drawing.Point(69, 31);
            this.MeshRenderer_Mesh_Input.Name = "MeshRenderer_Mesh_Input";
            this.MeshRenderer_Mesh_Input.Size = new System.Drawing.Size(126, 21);
            this.MeshRenderer_Mesh_Input.TabIndex = 1;
            // 
            // MeshRenderer_Mesh_Label
            // 
            this.MeshRenderer_Mesh_Label.AutoSize = true;
            this.MeshRenderer_Mesh_Label.Location = new System.Drawing.Point(15, 33);
            this.MeshRenderer_Mesh_Label.Name = "MeshRenderer_Mesh_Label";
            this.MeshRenderer_Mesh_Label.Size = new System.Drawing.Size(41, 15);
            this.MeshRenderer_Mesh_Label.TabIndex = 0;
            this.MeshRenderer_Mesh_Label.Text = "Mesh:";
            // 
            // SaveToolStripMenuItem
            // 
            this.SaveToolStripMenuItem.Image = global::ColonyPrefabManager.Properties.Resources.save;
            this.SaveToolStripMenuItem.Name = "SaveToolStripMenuItem";
            this.SaveToolStripMenuItem.Size = new System.Drawing.Size(114, 22);
            this.SaveToolStripMenuItem.Text = "Save";
            this.SaveToolStripMenuItem.Click += new System.EventHandler(this.SaveToolStripMenuItem_Click);
            // 
            // SaveAsToolStripMenuItem
            // 
            this.SaveAsToolStripMenuItem.Image = global::ColonyPrefabManager.Properties.Resources.save_as;
            this.SaveAsToolStripMenuItem.Name = "SaveAsToolStripMenuItem";
            this.SaveAsToolStripMenuItem.Size = new System.Drawing.Size(114, 22);
            this.SaveAsToolStripMenuItem.Text = "Save As";
            this.SaveAsToolStripMenuItem.Click += new System.EventHandler(this.SaveAsToolStripMenuItem_Click);
            // 
            // Animator_Default
            // 
            this.Animator_Default.Image = global::ColonyPrefabManager.Properties.Resources.star;
            this.Animator_Default.Location = new System.Drawing.Point(282, 16);
            this.Animator_Default.Name = "Animator_Default";
            this.Animator_Default.Size = new System.Drawing.Size(25, 25);
            this.Animator_Default.TabIndex = 4;
            this.Animator_Default.UseVisualStyleBackColor = true;
            this.Animator_Default.Click += new System.EventHandler(this.Animator_Default_Click);
            // 
            // Animator_Remove
            // 
            this.Animator_Remove.Image = global::ColonyPrefabManager.Properties.Resources.remove;
            this.Animator_Remove.Location = new System.Drawing.Point(344, 16);
            this.Animator_Remove.Name = "Animator_Remove";
            this.Animator_Remove.Size = new System.Drawing.Size(25, 25);
            this.Animator_Remove.TabIndex = 2;
            this.Animator_Remove.UseVisualStyleBackColor = true;
            this.Animator_Remove.Click += new System.EventHandler(this.Animator_Remove_Click);
            // 
            // Animator_Add
            // 
            this.Animator_Add.Image = global::ColonyPrefabManager.Properties.Resources.add;
            this.Animator_Add.Location = new System.Drawing.Point(313, 16);
            this.Animator_Add.Name = "Animator_Add";
            this.Animator_Add.Size = new System.Drawing.Size(25, 25);
            this.Animator_Add.TabIndex = 1;
            this.Animator_Add.UseVisualStyleBackColor = true;
            this.Animator_Add.Click += new System.EventHandler(this.Animator_Add_Click);
            // 
            // PrefabManager
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.ClientSize = new System.Drawing.Size(402, 434);
            this.Controls.Add(this.RemoveComponent);
            this.Controls.Add(this.ComponentList);
            this.Controls.Add(this.AddComponent);
            this.Controls.Add(this.menuStrip1);
            this.Controls.Add(this.Animator_Group);
            this.Controls.Add(this.Transform_Group);
            this.Controls.Add(this.Camera_Group);
            this.Controls.Add(this.Lighting_Group);
            this.Controls.Add(this.MeshRenderer_Group);
            this.Controls.Add(this.Collider_Group);
            this.Controls.Add(this.RigidBody_Group);
            this.Controls.Add(this.GameObject_Group);
            this.Controls.Add(this.AudioSource_Group);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "PrefabManager";
            this.Text = "Manage Prefab";
            ((System.ComponentModel.ISupportInitialize)(this.GameObject_ID_Input)).EndInit();
            this.GameObject_Group.ResumeLayout(false);
            this.GameObject_Group.PerformLayout();
            this.Transform_Group.ResumeLayout(false);
            this.Transform_Group.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.Transform_Scale_Input)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Transform_Rotation_Z_Input)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Transform_Rotation_Y_Input)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Transform_Rotation_X_Input)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Transform_Position_Z_Input)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Transform_Position_Y_Input)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Transform_Position_X_Input)).EndInit();
            this.Camera_Group.ResumeLayout(false);
            this.Camera_Group.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.Camera_FOV_Input)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Camera_NearPlane_Input)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Camera_FarPlane_Input)).EndInit();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.Lighting_Group.ResumeLayout(false);
            this.Lighting_Group.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.Lighting_Extra_W_Input)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Lighting_Extra_Z_Input)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Lighting_Extra_Y_Input)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Lighting_Extra_X_Input)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Lighting_Color_A_Input)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Lighting_Color_B_Input)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Lighting_Color_G_Input)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Lighting_Color_R_Input)).EndInit();
            this.AudioSource_Group.ResumeLayout(false);
            this.AudioSource_Group.PerformLayout();
            this.RigidBody_Group.ResumeLayout(false);
            this.RigidBody_Group.PerformLayout();
            this.Collider_Group.ResumeLayout(false);
            this.Collider_Group.PerformLayout();
            this.Animator_Group.ResumeLayout(false);
            this.Animator_Group.PerformLayout();
            this.MeshRenderer_Group.ResumeLayout(false);
            this.MeshRenderer_Group.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Button AddComponent;
        private System.Windows.Forms.ComboBox ComponentList;
        private System.Windows.Forms.NumericUpDown GameObject_ID_Input;
        private System.Windows.Forms.Label GameObject_ID_Label;
        private System.Windows.Forms.Label GameObject_Name_Label;
        private System.Windows.Forms.TextBox GameObject_Name_Input;
        private System.Windows.Forms.Label GameObject_Tag_Label;
        private System.Windows.Forms.TextBox GameObject_Tag_Input;
        private System.Windows.Forms.CheckBox GameObject_Transperent;
        private System.Windows.Forms.CheckBox GameObject_Dynamic;
        private System.Windows.Forms.GroupBox GameObject_Group;
        private System.Windows.Forms.Button RemoveComponent;
        private System.Windows.Forms.GroupBox Transform_Group;
        private System.Windows.Forms.Label Transform_Position_Label;
        private System.Windows.Forms.Label Transform_Position_Z_Label;
        private System.Windows.Forms.NumericUpDown Transform_Position_Z_Input;
        private System.Windows.Forms.Label Transform_Position_Y_Label;
        private System.Windows.Forms.NumericUpDown Transform_Position_Y_Input;
        private System.Windows.Forms.Label Transform_Position_X_Label;
        private System.Windows.Forms.NumericUpDown Transform_Position_X_Input;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.NumericUpDown Transform_Rotation_Z_Input;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.NumericUpDown Transform_Rotation_Y_Input;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.NumericUpDown Transform_Rotation_X_Input;
        private System.Windows.Forms.Label Transform_Rotation_Label;
        private System.Windows.Forms.NumericUpDown Transform_Scale_Input;
        private System.Windows.Forms.Label Transform_Scale_Label;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fIleToolStripMenuItem;
        private System.Windows.Forms.GroupBox Camera_Group;
        private System.Windows.Forms.Label Camera_FarPlane_Label;
        private System.Windows.Forms.Label Camera_FOV_Label;
        private System.Windows.Forms.Label Camera_NearPlane_Label;
        private System.Windows.Forms.NumericUpDown Camera_NearPlane_Input;
        private System.Windows.Forms.NumericUpDown Camera_FarPlane_Input;
        private System.Windows.Forms.NumericUpDown Camera_FOV_Input;
        private System.Windows.Forms.GroupBox Lighting_Group;
        private System.Windows.Forms.Label Lighting_Color_B_Label;
        private System.Windows.Forms.NumericUpDown Lighting_Color_B_Input;
        private System.Windows.Forms.Label Lighting_Color_G_Label;
        private System.Windows.Forms.NumericUpDown Lighting_Color_G_Input;
        private System.Windows.Forms.Label Lighting_Color_R_Label;
        private System.Windows.Forms.NumericUpDown Lighting_Color_R_Input;
        private System.Windows.Forms.Label Lighting_Color;
        private System.Windows.Forms.ColorDialog LightingColorDialog;
        private System.Windows.Forms.Label Lighting_Color_A_Label;
        private System.Windows.Forms.NumericUpDown Lighting_Color_A_Input;
        private System.Windows.Forms.Button Lighting_PickColor;
        private System.Windows.Forms.Label Lighting_Extra_Label;
        private System.Windows.Forms.Label Lighting_Extra_W_Label;
        private System.Windows.Forms.NumericUpDown Lighting_Extra_W_Input;
        private System.Windows.Forms.Label Lighting_Extra_Z_Label;
        private System.Windows.Forms.NumericUpDown Lighting_Extra_Z_Input;
        private System.Windows.Forms.Label Lighting_Extra_Y_Label;
        private System.Windows.Forms.NumericUpDown Lighting_Extra_Y_Input;
        private System.Windows.Forms.Label Lighting_Extra_X_Label;
        private System.Windows.Forms.NumericUpDown Lighting_Extra_X_Input;
        private System.Windows.Forms.ComboBox Lighting_LightType_Input;
        private System.Windows.Forms.Label Lighting_LightType;
        private System.Windows.Forms.GroupBox AudioSource_Group;
        private System.Windows.Forms.Button AudioSource_Browse;
        private System.Windows.Forms.TextBox AudioSource_ClipPath;
        private System.Windows.Forms.Label AudioSource_Clip;
        private System.Windows.Forms.OpenFileDialog AudioSource_FileDialog;
        private System.Windows.Forms.ToolStripMenuItem SaveToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem SaveAsToolStripMenuItem;
        private System.Windows.Forms.GroupBox RigidBody_Group;
        private System.Windows.Forms.Label RigidBody_Label;
        private System.Windows.Forms.GroupBox Collider_Group;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.GroupBox Animator_Group;
        private System.Windows.Forms.ListBox Animator_Animations;
        private System.Windows.Forms.Button Animator_Remove;
        private System.Windows.Forms.Button Animator_Add;
        private System.Windows.Forms.Label Animator_Label1;
        private System.Windows.Forms.GroupBox MeshRenderer_Group;
        private System.Windows.Forms.Label MeshRenderer_Mesh_Label;
        private System.Windows.Forms.Button MeshRenderer_Mesh_Browser;
        private System.Windows.Forms.TextBox MeshRenderer_Mesh_Input;
        private System.Windows.Forms.Button Animator_Default;
    }
}