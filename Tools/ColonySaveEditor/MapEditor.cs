using System.Drawing;
using System.Windows.Forms;

namespace ColonySaveEditor
{
	public partial class MapEditor : Form
	{
		public const int mapSize = 100;
		private int[,] height, iron, coal;
		private int selected = 0;
		private int cellSize;

		private Point ToPanelSpace(Point _point)
		{
			Point ret = new Point();
			ret.X = _point.X - pictureBox1.Left;
			ret.Y = _point.Y - pictureBox1.Top;
			return ret;
		}

		private void pictureBox1_Paint(object sender, PaintEventArgs e)
		{
			// Draw noise
			int[,] map;
			switch (selected)
			{
				case 0:
					map = height;
					break;

				case 1:
					map = iron;
					break;

				default:
					map = coal;
					break;
			}
			for (int i = 0; i < mapSize; i++)
			{
				for (int j = 0; j < mapSize; j++)
				{
					int color = map[i, j];
					e.Graphics.FillRectangle(new SolidBrush(Color.FromArgb(255, color, color, color)), i * cellSize, j * cellSize, cellSize, cellSize);
				}
			}
			// Draw grid
			for (int i = 1; i < mapSize; i++)
			{
				e.Graphics.DrawLine(Pens.Blue, i * cellSize, 0, i * cellSize, pictureBox1.Height);
				e.Graphics.DrawLine(Pens.Blue, 0, i * cellSize, pictureBox1.Width, i * cellSize);
			}
		}

		private void MapEditor_MouseDown(object sender, MouseEventArgs e)
		{
			selected = listBox1.SelectedIndex;
			int change = e.Button == MouseButtons.Left ? 10 : -10;
			Point clickPoint = e.Location;
			Point cell = new Point(clickPoint.X / cellSize, clickPoint.Y / cellSize);
			if (cell.X > 0 && cell.X < mapSize && cell.Y > 0 && cell.Y < mapSize)
			{
				switch (selected)
				{
					case 0:
						height[cell.X, cell.Y] += change;
						if (height[cell.X, cell.Y] < 0)
							height[cell.X, cell.Y] = 0;
						if (height[cell.X, cell.Y] > 255)
							height[cell.X, cell.Y] = 255;
						break;

					case 1:
						iron[cell.X, cell.Y] += change;
						if (iron[cell.X, cell.Y] < 0)
							iron[cell.X, cell.Y] = 0;
						if (iron[cell.X, cell.Y] > 255)
							iron[cell.X, cell.Y] = 255;
						break;

					default:
						coal[cell.X, cell.Y] += change;
						if (coal[cell.X, cell.Y] < 0)
							coal[cell.X, cell.Y] = 0;
						if (coal[cell.X, cell.Y] > 255)
							coal[cell.X, cell.Y] = 255;
						break;
				}
			}
			pictureBox1.Invalidate();
		}

		public MapEditor()
		{
			InitializeComponent();
			listBox1.SelectedIndex = 0;
			height = new int[mapSize, mapSize];
			iron = new int[mapSize, mapSize];
			coal = new int[mapSize, mapSize];
			for (int i = 0; i < mapSize; i++)
				for (int j = 0; j < mapSize; j++)
					height[i, j] = 255;
			cellSize = pictureBox1.Width / mapSize;
		}
	}
}