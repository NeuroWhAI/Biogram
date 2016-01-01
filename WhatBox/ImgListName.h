#pragma once

/*

현재 시스템상 텍스쳐리스트는 번호로 접근하는데
이것은 추후에 헷갈리는 문제를 유발할 가능성이 있으므로
여기에 열거체로 이름을 지정해준다.

*/





enum ImgListName_
{
	TxList_None,			// 자유 리소스
	TxList_Framework,		// 페이드인/아웃, 텍스트박스, 로그인버튼, 회원가입버튼 add...
	TxList_Particle,		// 파티클
	// add...
};

