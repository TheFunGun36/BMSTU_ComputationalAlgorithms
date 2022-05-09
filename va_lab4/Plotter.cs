using Godot;
using System;
using System.Collections.Generic;

public class Plotter : TextureRect
{
	private Func<double, double> _function;
	private Rect2 _mathematicalRect = new Rect2(-5.0f, -5.0f, 10.0f, 10.0f);
	private Image _pixmap = new Image();
	private int[] _plottedValues;

	public List<Vector2> Points { get; set; } = new List<Vector2>();
	public Func<double, double> Function
	{
		get { return _function; }
		set { _function = value; Replot(); }
	}
	public Rect2 MathematicalRect
	{
		get { return _mathematicalRect; }
		set { _mathematicalRect = value; Replot(); }
	}
	public void SetValue(int index, int value)
		=> _plottedValues[index] = value;

	[Export] public Color BackgroundColor { get; set; }
	[Export] public Color AxesColor { get; set; }
	[Export] public Color GridColor { get; set; }
	[Export] public Color PlotColor { get; set; }
	[Export] public Color PointColor { get; set; }

	public override void _Ready()
	{
		CreatePixmap();
		CreateTexture();
		ClearPixmap();
		_function = SampleFunction;
		_plottedValues = new int[(int)_pixmap.GetSize().x];
		RecalculatePlot();
	}
	private void CreatePixmap()
	{
		Rect2 r = GetViewportRect();
		_pixmap.Create((int)r.Size.y, (int)r.Size.y, false, Image.Format.Rgba8);
	}
	private void CreateTexture()
	{
		Texture = new ImageTexture();
		(Texture as ImageTexture).CreateFromImage(_pixmap);
	}
	private void ClearPixmap()
	{
		_pixmap.Fill(BackgroundColor);
		UpdateImage();
	}
	private void UpdateImage() => (Texture as ImageTexture).SetData(_pixmap);

	public void Replot()
	{
		RecalculatePlot();
		Update();
	}
	private void RecalculatePlot()
	{
		for (int x = 0; x < _plottedValues.Length; x++)
			_plottedValues[x] = (int)Math.Round(ToScreen((float)Function(ToMath(x, 0)), 1));
	}
	private Vector2 ToMath(Vector2 point)
	{
		for (int i = 0; i < 2; i++)
			point[i] = ToMath(point[i], i);

		return point;
	}
	private float ToMath(float value, int index)
		=> (1 - index * 2) * (value / _pixmap.GetSize()[index] * MathematicalRect.Size[index] + MathematicalRect.Position[index]);
	private Vector2 ToScreen(Vector2 point)
	{
		for (int i = 0; i < 2; i++)
			point[i] = ToScreen(point[i], i);

		return point;
	}
	private float ToScreen(float value, int index)
		=> ((1 - index * 2) * value - MathematicalRect.Position[index]) / MathematicalRect.Size[index] * _pixmap.GetSize()[index];

	public override void _Draw()
	{
		base._Draw();
		DrawAxes();
		DrawFunction();
		DrawPoints();
	}
	private void DrawAxes()
	{
		Vector2 center = ToScreen(Vector2.Zero);

		for (int i = 0; i < 2; i++)
		{
			if (center[i] >= 0 && center[i] < _pixmap.GetSize()[i])
			{
				Vector2 src = new Vector2();
				src[i] = center[i];
				src[1 - i] = 0;
				Vector2 dst = new Vector2();
				dst[i] = center[i];
				dst[1 - i] = _pixmap.GetSize()[1 - i];

				DrawLine(src, dst, AxesColor);
			}
		}
	}
	private void DrawFunction()
	{
		int prevVal = _plottedValues[0];
		for (int i = 0; i < _plottedValues.Length; i++)
		{
			DrawLine(new Vector2(i - 1, prevVal), new Vector2(i, _plottedValues[i]), PlotColor);
			prevVal = _plottedValues[i];
		}
	}
	private void DrawPoints()
	{
		foreach (Vector2 point in Points)
		{
			Vector2 screenPoint = ToScreen(point);
			if (screenPoint.x >= 0)
				DrawCircle(screenPoint, 3, PointColor);
		}
	}

	public double SampleFunction(double arg) => arg * arg * arg;
}
