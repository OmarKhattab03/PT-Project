
#include "Input.h"
#include "Output.h"

Input::Input(window* pW)
{
	pWind = pW; //point to the passed window
}

void Input::GetPointClicked(Point &P) const
{
	pWind->WaitMouseClick(P.x, P.y);	//Wait for mouse click
}

string Input::GetString(Output *pO) const 
{
	string Label;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if(Key == 13 )	//ENTER key is pressed
			return Label;
		if((Key == 8) && (Label.size() >= 1))	//BackSpace is pressed
			Label.resize(Label.size() -1 );			
		else
			Label += Key;
		if (pO)
			pO->PrintMessage(Label);
	}
}


double Input::GetValue(Output* pO) const	// Reads a double value from the user 
{
	///TODO: add code to read a double value from the user and assign it to D
	double D = 0;
	string Label;
	int ToCheckEndOfString=0, IndexPoint=0, MaxPower;
	bool PointAllocated = false , Initialize = false, IsNegative = false;


	while (!(Initialize))
	{
		Label = GetString(pO);
		Initialize = IsValue(Label);

		if (Initialize)
		{
			for (int i = 0; i < Label.size(); i++)
			{
				if (Label[i] == '.')
				{
					IndexPoint = i;
					PointAllocated = true;
				}
			}

			if (Label[0] == '-') // Checking for number negativity
				IsNegative = true;


			// To Calculate Number
			MaxPower = Label.size() - 1;

			if (PointAllocated)
				MaxPower -= (Label.size() - IndexPoint);
			

			for (int i = 0; i < Label.size(); i++)
			{
				if (Label[i] != '-' && Label[i] != '.')
				{
					int z = Label[i] - 48;
					double Power = pow(10, (MaxPower - i));
					if (Power < 1)
						Power *= 10;
					D += z * Power;
				}
			}

			if (IsNegative)
				D = (-1) * D;

			if (ToCheckEndOfString == Label.size())
				break;
		}

		//This function should make any needed validations on the entered text 
		// to make sure it is a double value (e.g. 12.5, -12.5, -23, -23., -23.0 �etc.).

		pO->PrintMessage("Please enter a value");


		}

	//Read a double value from the user
	return D;
}


string Input::GetVariable(Output*pO) const
{
	string VariableName = GetString(pO);
	while (!(IsVariable(VariableName)))
	{
		pO->PrintMessage("Enter a valid variable name:");
		VariableName = GetString(pO);
	}
	return VariableName;
}

string Input::GetArithOperator(Output* pO) const
{
	string Label = GetString(pO);


	while (Label != "+" && Label != "-" && Label != "*" && Label != "/")
	{
		pO->PrintMessage("Enter a valid operation:");
		Label = GetString(pO);
	}
	pO->PrintMessage(Label);
	return Label;
}

string Input::GetCompOperator(Output* pO)const
{
	string CompOperator = GetString(pO);
	while (CompOperator != "==" && CompOperator != "!=" && CompOperator != "<" && CompOperator != "<=" && CompOperator != ">" && CompOperator != ">=")
	{
		pO->PrintMessage("Enter a valid CompOperator:");
		CompOperator = GetString(pO);
	}
	pO->PrintMessage(CompOperator);
	return CompOperator;
}

ActionType Input::GetUserAction() const
{	
	//This function reads the position where the user clicks to determine the desired action

	int x,y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click
	
	if(UI.AppMode == DESIGN )	//application is in design mode
	{
		//[1] If user clicks on the Toolbar
		if ( y >= 0 && y < UI.ToolBarHeight)
		{	
			//Check whick Menu item was clicked
			//This assumes that menu items are lined up horizontally
			int ClickedItem = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on
			switch (ClickedItem)
			{
			case ITM_VALUE_ASSIGN: return ADD_VALUE_ASSIGN;
			case ITM_COND: return ADD_CONDITION;
			case ITM_EXIT: return EXIT;	
			default: return DSN_TOOL;
			}
		}
	
		//[2] User clicks on the drawing area
		if ( y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			if (x <= UI.DrawingAreaWidth)
				return DRAWING_AREA;	
			else
				return OUTPUT_AREA;
		}
		
		//[3] User clicks on the status bar
		return STATUS;
	}
	else	//Application is in Simulation mode
	{

		// TODO: This should be changed after creating the compelete simulation bar 
		return SWITCH_DSN_MODE;	// THIS SHOULD BE CHANGED
	}

}


Input::~Input()
{
}
