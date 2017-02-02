using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ColonyPrefabManager
{
    public partial class PrefabManager : Form
    {
        Transform transform = new Transform();
        GameObject gameObject = new GameObject();
        Camera camera = new Camera();
        Lighting lighting = new Lighting();
        AudioSource audioSource = new AudioSource();

        public PrefabManager()
        {
            InitializeComponent();

            // Initialize component list
            ComponentList.Items.Add(gameObject);
            ComponentList.Items.Add(transform);
            ComponentList.Items.Add(camera);
            ComponentList.Items.Add(lighting);
            ComponentList.Items.Add(audioSource);

            ComponentList.SelectedItem = ComponentList.Items[0];
            RemoveComponent.Enabled = false;
            AddComponent.Text = "Save Component";
            
            GameObject_Group.Visible = true;
            Transform_Group.Visible = false;
            Camera_Group.Visible = false;
            Lighting_Group.Visible = false;
            AudioSource_Group.Visible = false;
        }

        private void ComponentList_SelectedIndexChanged(object sender, EventArgs e)
        {
            // Check if selected is GameObject
            if (ComponentList.SelectedItem == gameObject)
                RemoveComponent.Enabled = false; // you cannot remove GameObject component
            else
                RemoveComponent.Enabled = true;

            // Reset button text
            AddComponent.Text = "Add Component";

            // GameObject settings
            if (ComponentList.SelectedItem == gameObject)
            {
                GameObject_Group.Visible = true;
                AddComponent.Text = "Save Component";
            }
            else GameObject_Group.Visible = false;

            // Transform settings
            if (ComponentList.SelectedItem == transform)
            {
                Transform_Group.Visible = true;
                if(transform.GetAdded()) AddComponent.Text = "Save Component";
            }
            else Transform_Group.Visible = false;

            // Camera settings
            if (ComponentList.SelectedItem == camera)
            {
                Camera_Group.Visible = true;
                if (camera.GetAdded()) AddComponent.Text = "Save Component";
            }
            else Camera_Group.Visible = false;

            // Lighting settings
            if (ComponentList.SelectedItem == lighting)
            {
                Lighting_Group.Visible = true;
                if (lighting.GetAdded()) AddComponent.Text = "Save Component";
            }
            else Lighting_Group.Visible = false;

            // AudioSource settings
            if (ComponentList.SelectedItem == audioSource)
            {
                AudioSource_Group.Visible = true;
                if (audioSource.GetAdded()) AddComponent.Text = "Save Component";
            }
            else AudioSource_Group.Visible = false;
        }

        public void AddComponent_Click(object sender, EventArgs e)
        {
            // Save Transform
            if (ComponentList.SelectedItem == transform)
            {
                if (!transform.GetAdded())
                {
                    transform.SetAdded(true);
                    AddComponent.Text = "Save Component";
                }
                transform.SetPosition(float.Parse(Transform_Position_X_Input.Text), float.Parse(Transform_Position_Y_Input.Text), float.Parse(Transform_Position_Z_Input.Text));
                transform.SetRotation(float.Parse(Transform_Rotation_X_Input.Text), float.Parse(Transform_Rotation_Y_Input.Text), float.Parse(Transform_Rotation_Z_Input.Text));
                transform.SetScale(float.Parse(Transform_Scale_Input.Text));
            }

            // Save GameObject
            if (ComponentList.SelectedItem == gameObject)
            {
                gameObject.SetId(int.Parse(GameObject_ID_Input.Text));
                gameObject.SetName(GameObject_Name_Input.Text);
                gameObject.SetTag(GameObject_Tag_Input.Text);
                gameObject.SetTransparent(GameObject_Transperent.Checked);
                gameObject.SetDynamic(GameObject_Dynamic.Checked);
            }

            // Save Camera
            if (ComponentList.SelectedItem == camera)
            {
                if (!camera.GetAdded())
                {
                    camera.SetAdded(true);
                    AddComponent.Text = "Save Component";
                }
                camera.SetFarPlane(float.Parse(Camera_FarPlane_Input.Text));
                camera.SetNearPlane(float.Parse(Camera_NearPlane_Input.Text));
                camera.SetFOV(float.Parse(Camera_FOV_Input.Text));
            }

            // Save Lighting
            if (ComponentList.SelectedItem == lighting)
            {
                if (!lighting.GetAdded())
                {
                    lighting.SetAdded(true);
                    AddComponent.Text = "Save Component";
                }
                lighting.SetColor(float.Parse(Lighting_Color_R_Input.Text), float.Parse(Lighting_Color_G_Input.Text), float.Parse(Lighting_Color_B_Input.Text), float.Parse(Lighting_Color_A_Input.Text));
                lighting.SetExtra(float.Parse(Lighting_Extra_X_Input.Text), float.Parse(Lighting_Extra_Y_Input.Text), float.Parse(Lighting_Extra_Z_Input.Text), float.Parse(Lighting_Extra_W_Input.Text));
                lighting.SetLightType(Lighting_LightType_Input.SelectedIndex);
            }

            // Save AudioSource
            if (ComponentList.SelectedItem == audioSource)
            {
                if (!audioSource.GetAdded())
                {
                    audioSource.SetAdded(true);
                    AddComponent.Text = "Save Component";
                }
                audioSource.SetSound(AudioSource_ClipPath.Text);
            }
        }

        private void RemoveComponent_Click(object sender, EventArgs e)
        {
            if (ComponentList.SelectedItem == transform)
            {
                transform.SetAdded(false);
                AddComponent.Text = "Add Component";
            }

            if (ComponentList.SelectedItem == camera)
            {
                camera.SetAdded(false);
                AddComponent.Text = "Add Component";
            }

            if (ComponentList.SelectedItem == lighting)
            {
                lighting.SetAdded(false);
                AddComponent.Text = "Add Component";
            }

            if (ComponentList.SelectedItem == audioSource)
            {
                audioSource.SetAdded(false);
                AddComponent.Text = "Add Component";
            }
        }

        private void Lighting_PickColor_Click(object sender, EventArgs e)
        {
            LightingColorDialog.ShowDialog();
            Lighting_Color_R_Input.Text = LightingColorDialog.Color.R.ToString();
            Lighting_Color_G_Input.Text = LightingColorDialog.Color.G.ToString();
            Lighting_Color_B_Input.Text = LightingColorDialog.Color.B.ToString();
            Lighting_Color_A_Input.Text = LightingColorDialog.Color.A.ToString();
        }

        private void AudioSource_Browse_Click(object sender, EventArgs e)
        {
            AudioSource_FileDialog.Filter = "WAVE (*.wav)|*.wav";
            if (AudioSource_FileDialog.ShowDialog() == DialogResult.OK)
            {
                AudioSource_ClipPath.Text = AudioSource_FileDialog.FileName;
            }
        }
    }
}
