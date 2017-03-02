using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Windows.Forms;

namespace BuildingCreator
{
	public struct Int3
	{
		public int x, y, z;
	}

	public partial class Form1 : Form
	{
		private List<Int3> gridSpaces = new List<Int3>();
		private int mapSize = 50;
		private int cellSize = 8;
		private Int3 origin = new Int3();

		public Form1()
		{
			InitializeComponent();
			origin.x = 25;
			origin.y = 25;
			origin.z = 0;
			panel1.Invalidate();
		}

		private void exitToolStripMenuItem_Click(object sender, EventArgs e)
		{
			Application.Exit();
		}

		private void loadToolStripMenuItem_Click(object sender, EventArgs e)
		{
			gridSpaces.Clear();
			OpenFileDialog dialog = new OpenFileDialog();
			if (dialog.ShowDialog() == DialogResult.OK)
			{
				StreamReader reader = new StreamReader(dialog.OpenFile());
				while (!reader.EndOfStream)
				{
					string line = reader.ReadLine();
					string[] lineVars = line.Split(' ');
					Int3 point = new Int3();
					point.x = int.Parse(lineVars[0]);
					point.y = int.Parse(lineVars[1]);
					point.z = int.Parse(lineVars[2]);
					gridSpaces.Add(point);
				}
				reader.Close();
			}
			panel1.Invalidate();
		}

		private void saveToolStripMenuItem_Click(object sender, EventArgs e)
		{
			SaveFileDialog dialog = new SaveFileDialog();
			if (dialog.ShowDialog() == DialogResult.OK)
			{
				StreamWriter writer = new StreamWriter(dialog.OpenFile());
				for (int i = 0; i < gridSpaces.Count; i++)
				{
					writer.Write(gridSpaces[i].x + " " + gridSpaces[i].y + " " + gridSpaces[i].z + "\n");
				}
				writer.Close();
			}
		}

		private void panel1_Paint(object sender, PaintEventArgs e)
		{
			// Clear Panel
			e.Graphics.Clear(Color.White);

			// Draw squares
			for (int i = 0; i < gridSpaces.Count; i++)
			{
				Int3 cell = gridSpaces[i];
				cell.x += origin.x;
				cell.y += origin.y;
				cell.z += origin.z;
				Rectangle rect = new Rectangle(cell.x * cellSize, cell.y * cellSize, cellSize, cellSize);
				Brush brush = Brushes.Red;
				if (gridSpaces[i].z == 0)
					brush = Brushes.Green;
				else if (gridSpaces[i].z == 1)
					brush = Brushes.Blue;
				e.Graphics.FillRectangle(brush, rect);
			}

			// Draw grid
			for (int i = 1; i < mapSize; i++)
			{
				e.Graphics.DrawLine(Pens.Blue, i * cellSize, 0, i * cellSize, panel1.Height);
				e.Graphics.DrawLine(Pens.Blue, 0, i * cellSize, panel1.Width, i * cellSize);
			}
		}

		private void radioButton1_CheckedChanged(object sender, EventArgs e)
		{
			if (radioButton1.Checked)
				label1.BackColor = radioButton1.BackColor;
			else
				label1.BackColor = radioButton2.BackColor;
		}
	}
}