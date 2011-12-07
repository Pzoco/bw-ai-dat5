class SpawnPrediction
{
    inputs = ();
    outputs = ();
    node_size = (80 40);
    HR_Desc = "";
    HR_OOBN_CheckConsistency = "1";
    HR_OOBN_FitExpand = "1";
    HR_Zoom_ZoomFactor = "100";
    HR_Groups_GroupColors = "";
    HR_Groups_GroupNames = "";
    HR_Groups_UserGroupsNo = "0";
    HR_Color_Interface = "21";
    HR_Color_Instance = "0";
    HR_Color_Function = "4";
    HR_Color_Utility = "36";
    HR_Color_Decision = "17";
    HR_Color_ContinuousChance = "48";
    HR_Color_DiscreteChance = "16";
    HR_Monitor_InitSD = "2";
    HR_Monitor_Utility_Arrange = "0";
    HR_Monitor_Mean_Variance = "1";
    HR_Monitor_Chance_Utility = "1";
    HR_Monitor_InitStates = "5";
    HR_Monitor_OpenGraph = "0";
    HR_Monitor_GraphPrecision = "100";
    HR_Monitor_AutoUpdGraph = "0";
    HR_Compile_MaxMinimalSeparators = "100000";
    HR_Compile_ApproxEpsilon = "1.0E-5";
    HR_Compile_Approximate = "0";
    HR_Compile_SaveToMemory = "0";
    HR_Compile_Compress = "0";
    HR_Compile_TriangMethod = "0";
    HR_Propagate_AutoNormal = "1";
    HR_Propagate_AutoSum = "1";
    HR_Propagate_Auto = "1";
    HR_Font_Italic = "0";
    HR_Font_Weight = "400";
    HR_Font_Size = "-12";
    HR_Font_Name = "javax.swing.plaf.FontUIResource[family=Tahoma,name=Tahoma,style=plain,size=11]";
    HR_Grid_GridShow = "0";
    HR_Grid_GridSnap = "0";
    HR_Grid_Y = "40";
    HR_Grid_X = "40";

    node TimingSeenTo
    {
	label = "";
	position = (984 176);
	states = ("AlmostNone" "Early" "Middle" "Late");
	HR_LinkMode = "[WorkerScout:0][WorkerScoutPositionFrom:0][WorkerScoutPositionFrom_1:0][WorkerScoutPositionTo:0]";
	HR_State_0 = "";
	HR_State_1 = "";
	HR_Desc = "";
	HR_LinkControlPoints = "";
	HR_State_2 = "";
	HR_State_3 = "";
	HR_NodeSize = "(135, 30)";
	HR_Group = "0";
    }

    node WorkerScoutPositionTo
    {
	label = "";
	position = (771 178);
	states = ("NE" "SE" "SW" "NW");
	HR_State_0 = "";
	HR_State_1 = "";
	HR_Desc = "";
	HR_LinkMode = "";
	HR_LinkControlPoints = "";
	HR_State_2 = "";
	HR_State_3 = "";
	HR_NodeSize = "(175, 59)";
	HR_Group = "0";
    }

    node EnemyNotAtNW
    {
	label = "";
	position = (463 360);
	states = ("True" "False");
	HR_NodeSize = "(128, 33)";
	HR_State_0 = "";
	HR_State_1 = "";
	HR_Desc = "";
	HR_Group = "0";
    }

    node EnemyNotAtSW
    {
	label = "";
	position = (432 358);
	states = ("True" "False");
	HR_NodeSize = "(107, 36)";
	HR_State_0 = "";
	HR_State_1 = "";
	HR_Desc = "";
	HR_Group = "0";
    }

    node EnemyNotAtSE
    {
	label = "";
	position = (404 357);
	states = ("True" "False");
	HR_NodeSize = "(104, 38)";
	HR_State_0 = "";
	HR_State_1 = "";
	HR_Desc = "";
	HR_Group = "0";
    }

    node EnemyNotAtNE
    {
	label = "";
	position = (380 359);
	states = ("True" "False");
	HR_NodeSize = "(99, 43)";
	HR_Group = "0";
	HR_Desc = "";
	HR_State_1 = "";
	HR_State_0 = "";
    }

    node TimingSeenFrom
    {
	label = "";
	position = (965 107);
	states = ("AlmostNone" "Early" "Middle" "Late");
	HR_NodeSize = "(135, 30)";
	HR_State_3 = "";
	HR_State_2 = "";
	HR_LinkControlPoints = "";
	HR_Group = "0";
	HR_Desc = "";
	HR_State_1 = "";
	HR_State_0 = "";
	HR_LinkMode = "[WorkerScout:0][WorkerScoutPositionFrom:0][WorkerScoutPositionFrom_1:0]";
    }

    node WorkerScoutPositionFrom
    {
	label = "";
	position = (775 85);
	states = ("NE" "SE" "SW" "NW");
	HR_NodeSize = "(175, 59)";
	HR_State_3 = "";
	HR_State_2 = "";
	HR_LinkControlPoints = "";
	HR_LinkMode = "";
	HR_Group = "0";
	HR_Desc = "";
	HR_State_1 = "";
	HR_State_0 = "";
    }

    node OverloardDirection
    {
	label = "";
	position = (215 132);
	states = ("From NE" "From SE" "From SW" "From NW");
	HR_LinkControlPoints = "";
	HR_LinkMode = "";
	HR_NodeSize = "(116, 33)";
	HR_State_3 = "";
	HR_State_2 = "";
	HR_Group = "0";
	HR_Desc = "";
	HR_State_1 = "";
	HR_State_0 = "";
    }

    node OurSpawn
    {
	label = "";
	position = (647 347);
	states = ("NE" "SE" "SW" "NW");
	HR_LinkControlPoints = "";
	HR_LinkMode = "[C1:0]";
	HR_NodeSize = "(97, 36)";
	HR_State_3 = "";
	HR_State_2 = "";
	HR_Group = "0";
	HR_Desc = "";
	HR_State_1 = "";
	HR_State_0 = "";
    }

    node EnemySpawn
    {
	label = "";
	position = (515 64);
	states = ("NE" "SE" "SW" "NW");
	HR_LinkControlPoints = "";
	HR_LinkMode = "[OverloardDirection:0][OurSpawn:0][WorkerScout:0][WorkerScoutPositionFrom:0][C1:0][EnemyNotAtNE:0][EnemyNotAtSE:0][EnemyNotAtSW:0][EnemyNotAtNW:0][WorkerScoutPositionFrom_1:0][WorkerScoutPositionTo:0]";
	HR_NodeSize = "(127, 61)";
	HR_State_3 = "";
	HR_State_2 = "";
	HR_Group = "0";
	HR_Desc = "";
	HR_State_1 = "";
	HR_State_0 = "";
    }

    potential (TimingSeenTo)
    {
	data = ( 1 1 1 1 );
    }

    potential (WorkerScoutPositionTo | EnemySpawn TimingSeenTo)
    {
	data = ((( 0.05 0.5 0.1 0.5 )	%  EnemySpawn=NE  TimingSeenTo=AlmostNone
		 ( 0.1 0.5 0.2 0.5 )	%  EnemySpawn=NE  TimingSeenTo=Early
		 ( 0.05 0.3 0.5 0.3 )	%  EnemySpawn=NE  TimingSeenTo=Middle
		 ( 0.4 0.5 0.2 0.5 ))	%  EnemySpawn=NE  TimingSeenTo=Late
		(( 0.5 0.05 0.5 0.1 )	%  EnemySpawn=SE  TimingSeenTo=AlmostNone
		 ( 0.5 0.1 0.2 0.5 )	%  EnemySpawn=SE  TimingSeenTo=Early
		 ( 0.3 0.05 0.3 0.5 )	%  EnemySpawn=SE  TimingSeenTo=Middle
		 ( 0.5 0.4 0.5 0.2 ))	%  EnemySpawn=SE  TimingSeenTo=Late
		(( 0.5 0.5 0.05 0.1 )	%  EnemySpawn=SW  TimingSeenTo=AlmostNone
		 ( 0.5 0.5 0.1 0.2 )	%  EnemySpawn=SW  TimingSeenTo=Early
		 ( 0.3 0.3 0.05 0.5 )	%  EnemySpawn=SW  TimingSeenTo=Middle
		 ( 0.5 0.5 0.4 0.2 ))	%  EnemySpawn=SW  TimingSeenTo=Late
		(( 0.5 0.1 0.5 0.05 )	%  EnemySpawn=NW  TimingSeenTo=AlmostNone
		 ( 0.5 0.2 0.5 0.1 )	%  EnemySpawn=NW  TimingSeenTo=Early
		 ( 0.3 0.5 0.3 0.05 )	%  EnemySpawn=NW  TimingSeenTo=Middle
		 ( 0.5 0.2 0.5 0.4 )));	%  EnemySpawn=NW  TimingSeenTo=Late
    }

    potential (EnemyNotAtNW | EnemySpawn)
    {
	data = (( 1 0 )	%  EnemySpawn=NE
		( 1 0 )	%  EnemySpawn=SE
		( 1 0 )	%  EnemySpawn=SW
		( 0 1 ));	%  EnemySpawn=NW
    }

    potential (EnemyNotAtSW | EnemySpawn)
    {
	data = (( 1 0 )	%  EnemySpawn=NE
		( 1 0 )	%  EnemySpawn=SE
		( 0 1 )	%  EnemySpawn=SW
		( 1 0 ));	%  EnemySpawn=NW
    }

    potential (EnemyNotAtSE | EnemySpawn)
    {
	data = (( 1 0 )	%  EnemySpawn=NE
		( 0 1 )	%  EnemySpawn=SE
		( 1 0 )	%  EnemySpawn=SW
		( 1 0 ));	%  EnemySpawn=NW
    }

    potential (EnemyNotAtNE | EnemySpawn)
    {
	data = (( 0 1 )	%  EnemySpawn=NE
		( 1 0 )	%  EnemySpawn=SE
		( 1 0 )	%  EnemySpawn=SW
		( 1 0 ));	%  EnemySpawn=NW
    }

    potential (TimingSeenFrom)
    {
	data = ( 0.25 0.25 0.25 0.25 );
    }

    potential (WorkerScoutPositionFrom | EnemySpawn TimingSeenFrom)
    {
	data = ((( 0.75 0.0833333 0.0833333 0.0833333 )	%  EnemySpawn=NE  TimingSeenFrom=AlmostNone
		 ( 0.277778 0.277778 0.166667 0.277778 )	%  EnemySpawn=NE  TimingSeenFrom=Early
		 ( 0.153846 0.230769 0.384615 0.230769 )	%  EnemySpawn=NE  TimingSeenFrom=Middle
		 ( 0.0714286 0.357143 0.214286 0.357143 ))	%  EnemySpawn=NE  TimingSeenFrom=Late
		(( 0.0833333 0.75 0.0833333 0.0833333 )	%  EnemySpawn=SE  TimingSeenFrom=AlmostNone
		 ( 0.277778 0.277778 0.277778 0.166667 )	%  EnemySpawn=SE  TimingSeenFrom=Early
		 ( 0.230769 0.153846 0.230769 0.384615 )	%  EnemySpawn=SE  TimingSeenFrom=Middle
		 ( 0.357143 0.0714286 0.357143 0.214286 ))	%  EnemySpawn=SE  TimingSeenFrom=Late
		(( 0.0833333 0.0833333 0.75 0.0833333 )	%  EnemySpawn=SW  TimingSeenFrom=AlmostNone
		 ( 0.166667 0.277778 0.277778 0.277778 )	%  EnemySpawn=SW  TimingSeenFrom=Early
		 ( 0.384615 0.230769 0.153846 0.230769 )	%  EnemySpawn=SW  TimingSeenFrom=Middle
		 ( 0.214286 0.357143 0.0714286 0.357143 ))	%  EnemySpawn=SW  TimingSeenFrom=Late
		(( 0.0833333 0.0833333 0.0833333 0.75 )	%  EnemySpawn=NW  TimingSeenFrom=AlmostNone
		 ( 0.277778 0.166667 0.277778 0.277778 )	%  EnemySpawn=NW  TimingSeenFrom=Early
		 ( 0.230769 0.384615 0.230769 0.153846 )	%  EnemySpawn=NW  TimingSeenFrom=Middle
		 ( 0.357143 0.214286 0.357143 0.0714286 )));	%  EnemySpawn=NW  TimingSeenFrom=Late
    }

    potential (OverloardDirection | EnemySpawn)
    {
	data = (( 0.9 0.033333 0.033333 0.033333 )	%  EnemySpawn=NE
		( 0.033333 0.9 0.033333 0.033333 )	%  EnemySpawn=SE
		( 0.033333 0.033333 0.9 0.033333 )	%  EnemySpawn=SW
		( 0.033333 0.033333 0.033333 0.9 ));	%  EnemySpawn=NW
    }

    potential (OurSpawn | EnemySpawn)
    {
	data = (( 0 0.333333 0.333333 0.333333 )	%  EnemySpawn=NE
		( 0.333333 0 0.333333 0.333333 )	%  EnemySpawn=SE
		( 0.333333 0.333333 0 0.333333 )	%  EnemySpawn=SW
		( 0.333333 0.333333 0.333333 0 ));	%  EnemySpawn=NW
    }

    potential (EnemySpawn)
    {
	data = ( 0.25 0.25 0.25 0.25 );
    }
} % class SpawnPrediction
