#include "Controller.h"

Controller::Controller(TChannel* Path, TChannel* NewPath, TChannel* Img, TChannel* Start, TChannel* Stop, TChannel* Take, TChannel* Ready, TChannel* Finish)
{
	this->Path = Path;
	this->NewPath = NewPath;
	this->Finish = Finish;

	this->Img = Img;

	this->Start = Start;
	this->Stop = Stop;

	this->Take = Take;
	this->Ready = Ready;
}

void Controller::start()
{
	while (true)
	{
		bool path = getPathData();

		if (path)
		{
			bool obstacle = getCameraData();

			if (!obstacle)
			{
				sendStartMoving();
				getStopMoving();
			}

			sendStopData(obstacle);
		}
		else
		{
			sendTake();
			getReady();
			sendFinish();
		}
	}
}

bool Controller::getPathData()
{
	cout << "\nКОНТРОЛЛЕР .1_1: ожидание команды Навигатора...";

	TData data;
	Path->get(&data);

	if (data.getNumber() != 0)
	{
		cout << "\nКОНТРОЛЛЕР .1_2: получена команда - продолжить движение";
		return true;
	}
	else
	{
		cout << "\nКОНТРОЛЛЕР .1_2: получена команда - точка назначения достигнута, собираем грунт";
		return false;
	}
}

bool Controller::getCameraData()
{
	cout << "\nКОНТРОЛЛЕР .2_1: ожидание изображения с Камеры...";

	TData data;
	Img->get(&data);

	if (data.getNumber() % 3 == 0)
	{
		cout << "\nКОНТРОЛЛЕР .2_2: получено изображение с Камеры #" << data.getNumber() << " - обнаружено препятствие";
		return true;
	}
	else
	{
		cout << "\nКОНТРОЛЛЕР .2_2: получено изображение с Камеры #" << data.getNumber() << " - препятствий нет";
		return false;
	}
}

void Controller::sendStartMoving()
{
	cout << "\nКОНТРОЛЛЕР .3: отправка команды в Модуль передвижения...";

	TData data(0, 4, "5 метров");
	Start->put(data);
}

void Controller::getStopMoving()
{
	cout << "\nКОНТРОЛЛЕР .4_1: ожидание сообщения о завершении с Модуля передвижения...";

	TData data;
	Stop->get(&data);

	cout << "\nКОНТРОЛЛЕР .4_2: получено сообщение о завершении движения с Модуля передвижения";
}

void Controller::sendStopData(bool obstacle)
{
	cout << "\nКОНТРОЛЛЕР .5: отправка сообщения об остановке в Навигатор...";

	TData data(obstacle, 4, "остановились");
	NewPath->put(data);
}

void Controller::sendTake()
{
	cout << "\nКОНТРОЛЛЕР .6: отправка команды 'начать сбор грунта' в Манипулятор...";

	TData data(0, 4, "собрать");
	Take->put(data);
}

void Controller::getReady()
{
	cout << "\nКОНТРОЛЛЕР .7_1: ожидание сообщения о завершении от Манипулятора...";

	TData data;
	Ready->get(&data);

	cout << "\nКОНТРОЛЛЕР .7_2: получено сообщение о завершении от Манипулятора";
}

void Controller::sendFinish()
{
	cout << "\nКОНТРОЛЛЕР .8: отправка сообщения о завершении миссии в Коммуникационный модуль...";

	TData data(0, 4, "закончили");
	Finish->put(data);
}
