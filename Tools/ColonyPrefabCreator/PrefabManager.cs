using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
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
        Light lighting = new Light();
        AudioSource audioSource = new AudioSource();
        RigidBody rigidBody = new RigidBody();
        Collider collider = new Collider();
        public string m_filePath = "0";

        public PrefabManager(string filePath = "0")
        {
            InitializeComponent();

            if(filePath != "0")
                ReadFromBinary(filePath);

            // Initialize component list
            ComponentList.Items.Add(gameObject);
            ComponentList.Items.Add(transform);
            ComponentList.Items.Add(camera);
            ComponentList.Items.Add(lighting);
            ComponentList.Items.Add(audioSource);
            ComponentList.Items.Add(rigidBody);
            ComponentList.Items.Add(collider);

            ComponentList.SelectedItem = ComponentList.Items[0];
            RemoveComponent.Enabled = false;
            AddComponent.Text = "Save Component";
            
            GameObject_Group.Visible = true;
            Transform_Group.Visible = false;
            Camera_Group.Visible = false;
            Lighting_Group.Visible = false;
            AudioSource_Group.Visible = false;
            RigidBody_Group.Visible = false;
            Collider_Group.Visible = false;
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

            // RigidBody settings
            if (ComponentList.SelectedItem == rigidBody)
            {
                RigidBody_Group.Visible = true;
                if (rigidBody.GetAdded()) AddComponent.Text = "Save Component";
            }
            else RigidBody_Group.Visible = false;

            // Collider settings
            if (ComponentList.SelectedItem == collider)
            {
                Collider_Group.Visible = true;
                if (collider.GetAdded()) AddComponent.Text = "Save Component";
            }
            else Collider_Group.Visible = false;
        }

        private void AddComponent_Click(object sender, EventArgs e)
        {
            // Save GameObject
            if (ComponentList.SelectedItem == gameObject)
            {
                gameObject.SetId(int.Parse(GameObject_ID_Input.Text));
                gameObject.SetName(GameObject_Name_Input.Text);
                gameObject.SetTag(GameObject_Tag_Input.Text);
                gameObject.SetTransparent(GameObject_Transperent.Checked);
                gameObject.SetDynamic(GameObject_Dynamic.Checked);
            }

            // Save Transform
            if (ComponentList.SelectedItem == transform)
            {
                if (!transform.GetAdded())
                {
                    transform.SetAdded(true);
                    gameObject.m_Components.Add(transform.GetId());
                    AddComponent.Text = "Save Component";
                }
                transform.SetPosition(float.Parse(Transform_Position_X_Input.Text), float.Parse(Transform_Position_Y_Input.Text), float.Parse(Transform_Position_Z_Input.Text));
                transform.SetRotation(float.Parse(Transform_Rotation_X_Input.Text), float.Parse(Transform_Rotation_Y_Input.Text), float.Parse(Transform_Rotation_Z_Input.Text));
                transform.SetScale(float.Parse(Transform_Scale_Input.Text));
            }

            // Save Camera
            if (ComponentList.SelectedItem == camera)
            {
                if (!camera.GetAdded())
                {
                    camera.SetAdded(true);
                    gameObject.m_Components.Add(camera.GetId());
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
                    gameObject.m_Components.Add(lighting.GetId());
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
                    gameObject.m_Components.Add(audioSource.GetId());
                    AddComponent.Text = "Save Component";
                }
                audioSource.SetClip(AudioSource_ClipPath.Text);
            }

            // Save RigidBody
            if (ComponentList.SelectedItem == rigidBody)
            {
                if (!rigidBody.GetAdded())
                {
                    rigidBody.SetAdded(true);
                    gameObject.m_Components.Add(rigidBody.GetId());
                    AddComponent.Text = "Save Component";
                }
            }

            // Save Collider
            if (ComponentList.SelectedItem == collider)
            {
                if (!collider.GetAdded())
                {
                    collider.SetAdded(true);
                    gameObject.m_Components.Add(collider.GetId());
                    AddComponent.Text = "Save Component";
                }
            }
        }

        private void RemoveComponent_Click(object sender, EventArgs e)
        {
            if (ComponentList.SelectedItem == transform)
            {
                transform.SetAdded(false);
                gameObject.m_Components.Remove(transform.GetId());
                AddComponent.Text = "Add Component";
            }

            if (ComponentList.SelectedItem == camera)
            {
                camera.SetAdded(false);
                gameObject.m_Components.Remove(camera.GetId());
                AddComponent.Text = "Add Component";
            }

            if (ComponentList.SelectedItem == lighting)
            {
                lighting.SetAdded(false);
                gameObject.m_Components.Remove(lighting.GetId());
                AddComponent.Text = "Add Component";
            }

            if (ComponentList.SelectedItem == audioSource)
            {
                audioSource.SetAdded(false);
                gameObject.m_Components.Remove(audioSource.GetId());
                AddComponent.Text = "Add Component";
            }

            if (ComponentList.SelectedItem == rigidBody)
            {
                rigidBody.SetAdded(false);
                gameObject.m_Components.Remove(rigidBody.GetId());
                AddComponent.Text = "Add Component";
            }

            if (ComponentList.SelectedItem == collider)
            {
                collider.SetAdded(false);
                gameObject.m_Components.Remove(collider.GetId());
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

        private void SaveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if(m_filePath != "0")
                WriteToBinary(m_filePath);
            else
                SaveAsToolStripMenuItem_Click(sender, e);
        }

        private void SaveAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveDialog = new SaveFileDialog();
            saveDialog.Filter = ".prefab|*.prefab";
            if (saveDialog.ShowDialog() == DialogResult.OK)
            {
                m_filePath = saveDialog.FileName;
                string fileName = Path.GetFileName(m_filePath);
                this.Text = "Manage Prefab - " + fileName;
                WriteToBinary(m_filePath);
            }
        }

        private void WriteToBinary(string path)
        {
            // Sort components ids
            gameObject.m_Components.Sort();

            using (BinaryWriter writer = new BinaryWriter(File.Open(path, FileMode.Create)))
            {
                byte delimiter = 1;

                // Write GameObject
                writer.Write(gameObject.GetId());
                writer.Write(gameObject.GetName().Length);
                writer.Write(gameObject.GetName());
                writer.Write(gameObject.GetTag().Length);
                writer.Write(gameObject.GetTag());
                writer.Write(gameObject.GetTransparent());
                writer.Write(gameObject.GetDynamic());
                // Write all enabled components
                writer.Write(gameObject.m_Components.Count);
                for(int i = 0; i < gameObject.m_Components.Count; ++i)
                    writer.Write(gameObject.m_Components[i]);
                // Write delimiter
                writer.Write(delimiter);

                // Write Transform -- id = 1
                if (transform.GetAdded())
                {
                    writer.Write(transform.GetPosition()[0]);
                    writer.Write(transform.GetPosition()[1]);
                    writer.Write(transform.GetPosition()[2]);
                    writer.Write(transform.GetRotation()[0]);
                    writer.Write(transform.GetRotation()[1]);
                    writer.Write(transform.GetRotation()[2]);
                    writer.Write(transform.GetScale());
                    // Write delimiter
                    writer.Write(delimiter);
                }

                // Write RigidBody -- id = 2
                if (audioSource.GetAdded())
                {
                    // Write delimiter
                    writer.Write(delimiter);
                }

                // Write Collider -- id = 3
                if (collider.GetAdded())
                {
                    // Write delimiter
                    writer.Write(delimiter);
                }

                // Write Camera -- id = 4
                if (camera.GetAdded())
                {
                    writer.Write(camera.GetFarPlane());
                    writer.Write(camera.GetNearPlane());
                    writer.Write(camera.GetFOV());
                    // Write delimiter
                    writer.Write(delimiter);
                }

                // Write Light -- id = 8
                if (lighting.GetAdded())
                {
                    writer.Write(lighting.GetColor()[0]);
                    writer.Write(lighting.GetColor()[1]);
                    writer.Write(lighting.GetColor()[2]);
                    writer.Write(lighting.GetColor()[3]);
                    writer.Write(lighting.GetExtra()[0]);
                    writer.Write(lighting.GetExtra()[1]);
                    writer.Write(lighting.GetExtra()[2]);
                    writer.Write(lighting.GetExtra()[3]);
                    writer.Write(lighting.GetLightType());
                    // Write delimiter
                    writer.Write(delimiter);
                }

                // Write AudioSource -- id = 11
                if (audioSource.GetAdded())
                {
                    writer.Write(audioSource.GetClip());
                    // Write delimiter
                    writer.Write(delimiter);
                }

                writer.Close();
                
                // Send message
                string message = "File Successfully Saved";
                string caption = "Message";
                DialogResult result = MessageBox.Show(message, caption);
            }
        }

        private void ReadFromBinary(string path)
        {
            if (File.Exists(path))
            {
                using (BinaryReader reader = new BinaryReader(File.Open(path, FileMode.Open)))
                {
                    m_filePath = path;
                    string fileName = Path.GetFileName(m_filePath);
                    this.Text = "Manage Prefab - " + fileName;

                    // Load GameObject
                    gameObject.SetId(reader.ReadInt32());
                    reader.ReadInt32();
                    gameObject.SetName(reader.ReadString());
                    reader.ReadInt32();
                    gameObject.SetTag(reader.ReadString());
                    gameObject.SetTransparent(reader.ReadBoolean());
                    gameObject.SetDynamic(reader.ReadBoolean());
                    int numOfComponents = reader.ReadInt32();
                    for(int i = 0; i < numOfComponents; ++i)
                        gameObject.m_Components.Add(reader.ReadInt32());
                    reader.ReadByte();

                    // Load Transform -- id = 1
                    if (gameObject.m_Components.Contains(transform.GetId()))
                    {
                        transform.SetAdded(true);
                        transform.SetPosition(reader.ReadSingle(), reader.ReadSingle(), reader.ReadSingle());
                        transform.SetRotation(reader.ReadSingle(), reader.ReadSingle(), reader.ReadSingle());
                        transform.SetScale(reader.ReadSingle());
                        reader.ReadByte();
                    }

                    // Load RigidBody -- id = 2
                    if (gameObject.m_Components.Contains(rigidBody.GetId()))
                    {
                        rigidBody.SetAdded(true);
                        reader.ReadByte();
                    }

                    // Load Collider -- id = 3
                    if (gameObject.m_Components.Contains(collider.GetId()))
                    {
                        collider.SetAdded(true);
                        reader.ReadByte();
                    }

                    // Load Camera -- id = 4
                    if (gameObject.m_Components.Contains(camera.GetId()))
                    {
                        camera.SetAdded(true);
                        camera.SetFarPlane(reader.ReadSingle());
                        camera.SetNearPlane(reader.ReadSingle());
                        camera.SetFOV(reader.ReadSingle());
                        reader.ReadByte();
                    }
                    
                    // Load Light -- id = 8
                    if (gameObject.m_Components.Contains(lighting.GetId()))
                    {
                        lighting.SetAdded(true);
                        lighting.SetColor(reader.ReadSingle(), reader.ReadSingle(), reader.ReadSingle(), reader.ReadSingle());
                        lighting.SetExtra(reader.ReadSingle(), reader.ReadSingle(), reader.ReadSingle(), reader.ReadSingle());
                        lighting.SetLightType(reader.ReadInt32());
                        reader.ReadByte();
                    }

                    // Load AudioSource -- id = 11
                    if (gameObject.m_Components.Contains(audioSource.GetId()))
                    {
                        audioSource.SetAdded(true);
                        audioSource.SetClip(reader.ReadString());
                        reader.ReadByte();
                    }

                    AssignValues();
                    reader.Close();
                }
            }
        }

        private void AssignValues()
        {
            GameObject_ID_Input.Text = gameObject.GetId().ToString();
            GameObject_Name_Input.Text = gameObject.GetName();
            GameObject_Tag_Input.Text = gameObject.GetTag();
            GameObject_Transperent.Checked = gameObject.GetTransparent();
            GameObject_Dynamic.Checked = gameObject.GetDynamic();

            if (transform.GetAdded())
            {
                Transform_Position_X_Input.Text = transform.GetPosition()[0].ToString();
                Transform_Position_Y_Input.Text = transform.GetPosition()[1].ToString();
                Transform_Position_Z_Input.Text = transform.GetPosition()[2].ToString();
                Transform_Rotation_X_Input.Text = transform.GetRotation()[0].ToString();
                Transform_Rotation_Y_Input.Text = transform.GetRotation()[1].ToString();
                Transform_Rotation_Z_Input.Text = transform.GetRotation()[2].ToString();
                Transform_Scale_Input.Text = transform.GetScale().ToString();
            }

            if (camera.GetAdded())
            {
                Camera_FarPlane_Input.Text = camera.GetFarPlane().ToString();
                Camera_NearPlane_Input.Text = camera.GetNearPlane().ToString();
                Camera_FOV_Input.Text = camera.GetFOV().ToString();
            }

            if (lighting.GetAdded())
            {
                Lighting_Color_R_Input.Text = lighting.GetColor()[0].ToString();
                Lighting_Color_G_Input.Text = lighting.GetColor()[1].ToString();
                Lighting_Color_B_Input.Text = lighting.GetColor()[2].ToString();
                Lighting_Color_A_Input.Text = lighting.GetColor()[3].ToString();
                Lighting_Extra_X_Input.Text = lighting.GetExtra()[0].ToString();
                Lighting_Extra_Y_Input.Text = lighting.GetExtra()[1].ToString();
                Lighting_Extra_Z_Input.Text = lighting.GetExtra()[2].ToString();
                Lighting_Extra_W_Input.Text = lighting.GetExtra()[3].ToString();
                Lighting_LightType_Input.SelectedIndex = lighting.GetLightType();
            }

            if (audioSource.GetAdded())
            {
                AudioSource_ClipPath.Text = audioSource.GetClip();
            }
        }
    }
}
