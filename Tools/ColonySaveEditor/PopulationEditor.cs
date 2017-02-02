using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ColonySaveEditor
{
	public partial class PopulationEditor : Form
	{
		public PopulationEditor()
		{
			InitializeComponent();
		}

		private void button1_Click(object sender, EventArgs e)
		{
			dataGridView1.Rows.Add();
		}

		private void button2_Click(object sender, EventArgs e)
		{
			try
			{
				int rowIndex = dataGridView1.SelectedCells[0].RowIndex;
				dataGridView1.Rows.RemoveAt(rowIndex);
			}
			catch (InvalidOperationException)
			{
			}
		}
	}
}