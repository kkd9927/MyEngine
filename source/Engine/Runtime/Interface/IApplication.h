#pragma once

class IApplication
{
public:
	virtual ~IApplication() {}

	/**
	 * @brief 실행에 필요한 자원의 획득, 폐기 및 메인 루프를 실행합니다.
	 */
	virtual void run() = 0;
};
