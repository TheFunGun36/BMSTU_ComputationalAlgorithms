using Godot;
using System;

public class Row : HBoxContainer
{
	private SpinBox _xSpin;
	private SpinBox _ySpin;
	private SpinBox _zSpin;
	private SpinBox _weightSpin;

	public double X { get => _xSpin.Value; set => _xSpin.Value = value; }
	public double Y { get => _ySpin.Value; set => _ySpin.Value = value; }
	public double Z { get => _zSpin.Value; set => _zSpin.Value = value;}
	public double Weight { get => _weightSpin.Value; set => _weightSpin.Value = value; }
	public int Index;

	[Export] public NodePath XPath;
	[Export] public NodePath YPath;
	[Export] public NodePath ZPath;
	[Export] public NodePath WeightPath;
	[Signal] public delegate void Changed(int index);

	public override void _Ready()
	{
		_xSpin = GetNode<SpinBox>(XPath);
		_ySpin = GetNode<SpinBox>(YPath);
		_zSpin = GetNode<SpinBox>(ZPath);
		_weightSpin = GetNode<SpinBox>(WeightPath);
	}

	public void OnChanged(float f)
		=> EmitSignal("Changed", Index);

	public void SetZVisible(bool value)
	{
		_zSpin.Visible = value;
	}
}
