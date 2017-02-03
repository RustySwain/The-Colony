using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using ColonyPrefabManager;

namespace ColonyPrefabCreator
{
    public partial class MainWindow : Form
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void NewPrefab_Click(object sender, EventArgs e)
        {
            PrefabManager newWindow = new PrefabManager();
            newWindow.Show();
        }

        private void LoadPrefab_Click(object sender, EventArgs e)
        {
            LoadPrefabDialog.Filter = "*.prefab|*.prefab";
            if (LoadPrefabDialog.ShowDialog() == DialogResult.OK)
            {
                PrefabManager newWindow = new PrefabManager(LoadPrefabDialog.FileName);
                newWindow.Show();
            }
        }

        private void Exit_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }
    }
}
