using Godot;
using System;

public class Calculate : Button
{
	private Table _table;
	private LineEdit _lineResult;
	private OptionButton _option;
	private SpinBox _spinX;
	private SpinBox _spinY;
	
	[Export] NodePath TablePath { get; set; }
	[Export] NodePath ResultPath { get; set; }
	[Export] NodePath ModePath { get; set; }
	[Export] NodePath SpinXPath { get; set; }
	[Export] NodePath SpinYPath { get; set; }
	
	public override void _Ready()
	{
		_table = GetNode<Table>(TablePath);
		_lineResult = GetNode<LineEdit>(ResultPath); 
		_option = GetNode<OptionButton>(ModePath);
		_spinX = GetNode<SpinBox>(SpinXPath);
		_spinY = GetNode<SpinBox>(SpinYPath);
	}
	
	private void OnPressed()
	{
		double x = _spinX.Value;
		double y = _spinY.Value;
		if (!_spinY.Visible)
			_lineResult.Text = _table.ApproxValue(x).ToString();
		else if (_option.Selected == 0)
			_lineResult.Text = _table.PlaneFunction(x, y).ToString();
		else
			_lineResult.Text = _table.ParaboloidFunction(x, y).ToString();
	}
}
