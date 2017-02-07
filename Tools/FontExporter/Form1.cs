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

namespace FontExporter
{
	public partial class Form1 : Form
	{
		private Bitmap bm;
		private string savePath;
		private List<int> starts = new List<int>();
		private List<int> breaks = new List<int>();
		private int top, bottom;

		public Form1()
		{
			InitializeComponent();
		}

		private bool IsEmpty(int _column)
		{
			for (int i = 0; i < bm.Height; i++)
			{
				Color c = bm.GetPixel(_column, i);
				if (c.A > 0)
					return false;
			}
			return true;
		}

		private bool EmptyRow(int _row)
		{
			for (int i = 0; i < bm.Width; i++)
			{
				Color c = bm.GetPixel(i, _row);
				if (c.A > 0)
					return false;
			}
			return true;
		}

		private void FindMaxMin()
		{
			for (int i = bm.Height - 1; i >= 0; i--)
			{
				if (!EmptyRow(i))
					break;
				top = i;
			}
			for (int i = 0; i < bm.Height; i++)
			{
				if (!EmptyRow(i))
					break;
				bottom = i;
			}
		}

		private void Analiyze()
		{
			FindMaxMin();
			bool onBreak = true;
			for (int i = 0; i < bm.Width; i++)
			{
				bool empty = IsEmpty(i);
				if (onBreak && !empty)
				{
					onBreak = false;
					starts.Add(i);
				}
				else if (!onBreak && empty)
				{
					onBreak = true;
					breaks.Add(i);
				}
			}
		}

		private void button2_Click(object sender, EventArgs e) // Load
		{
			OpenFileDialog ofd = new OpenFileDialog();
			if (ofd.ShowDialog() == DialogResult.OK)
			{
				bm = new Bitmap(ofd.FileName);
				savePath = ofd.FileName + ".fontsheet";
				Analiyze();
			}
		}

		private void button1_Click(object sender, EventArgs e) // Export
		{
			string text = textBox1.Text;
			StreamWriter writer = new StreamWriter(savePath, false, Encoding.UTF8);
			writer.Write(bm.Width + " " + bm.Height + " " + bottom + " " + top + "\n");
			for (int i = 0; i < text.Length; i++)
			{
				writer.Write(text[i] + " ");
				writer.Write(starts[i] + " ");
				writer.Write(breaks[i] - starts[i] + "\n");
			}
			writer.Close();
		}
	}
}