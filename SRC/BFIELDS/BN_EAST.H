#undef NODE
#define	NODE(num)		UID_BNE_##num##_XX
//Example
//		{	//LEVEL 5 //ambush at back
//		PLACE(		5A,MOUNTAINPASS),
//	/*flanks*/		{UID_NULL,UID_NULL,F::NOT_LINKED},
//	/*in*/			{IN(5A),L::ATTACKEASY,
//	/*reinforce/attack*/	BF_ReinforceOnRoad,BF_AttackRoadSide,		
//	/*defend/retreat*/		BF_LayRoadAmbush,BF_EnterAmbush},
//	/*out*/			{OUT(5A),L::NOADV,
//	/*reinforce/attack*/	BF_ReinforceOnRoad,BF_AttackRoadSide,		
//	/*defend/retreat*/		BF_LayRoadAmbush,BF_EnterAmbushRoad},
//	/*inroute*/		{NODE(6A),
//					BF_BThinRoad,BF_BThinRoad,		BF_RThinRoad,BF_RThinRoad}
//		},


LocalUID::SuperBattleDesc	eastbattledescs[]=
{




	 ////////////////// END OF LIST ///////////////////////////
{{NULL}}
};

