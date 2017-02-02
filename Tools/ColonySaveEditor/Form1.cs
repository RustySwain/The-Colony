using System.Windows.Forms;

namespace ColonySaveEditor
{
	public partial class Form1 : Form
	{
		public Form1()
		{
			InitializeComponent();
		}

		private void button1_Click(object sender, System.EventArgs e)
		{
			MapEditor editor = new MapEditor();
			editor.Show();
		}

		private void button2_Click(object sender, System.EventArgs e)
		{
			PopulationEditor editor = new PopulationEditor();
			editor.Show();
		}

		private void button3_Click(object sender, System.EventArgs e)
		{
		}

		private void loadToolStripMenuItem_Click(object sender, System.EventArgs e)
		{
		}

		private void newToolStripMenuItem_Click(object sender, System.EventArgs e)
		{
		}
	}
}