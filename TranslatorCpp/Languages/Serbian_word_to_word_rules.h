﻿// Именица->Именица:
{ L"*ац",       L"*чић",	имен, имен, { муш }, { муш, дем } }, //деминутив - мушкарац 
{ L"*а",	L"*ица",	имен, имен, { жен }, { жен, дем } }, //деминутив - жена
{ L"*а",	L"*етина",	имен, имен, { жен }, { жен, ауг } }, //аугментатив - женетина

// Глагол->Именица:
{ L"*ти",	L"*ње",		глаг, имен, { }, { сред } },
{ L"*ити",	L"*ење",	глаг, имен, { }, { сред } },
{ L"*лети",	L"*љење",	глаг, имен, { }, { сред } },
{ L"видети",L"виђање",	глаг, имен, { }, { сред } },
{ L"јести",	L"једење",	глаг, имен, { }, { сред } },
{ L"пити",	L"пијење",	глаг, имен, { }, { сред } },
{ L"бити",	L"",		глаг, имен, { }, { сред } },
{ L"желети",L"",		глаг, имен, { }, { сред } },
{ L"радити",L"",		глаг, имен, { }, { сред } },
{ L"хтети",	L"",		глаг, имен, { }, { сред } },
{ L"чути",	L"",		глаг, имен, { }, { сред } },

	// Глагол->Прилог:
{ L"*ати",	L"*ајући",	глаг, прил },			//гледати, дати

// Глагол->Придев:
{ L"*ти",	L"*н",		глаг, прид, { прел } },	//гледати, дати
{ L"*ити",	L"*ен",		глаг, прид, { прел } },	//говорити, учен
{ L"*зити",	L"*жен",	глаг, прид, { прел } },	//газити, заразити, пазити
{ L"видети",L"виђен",	глаг, прид, { прел } },
{ L"јести",	L"једен",	глаг, прид, { прел } },
{ L"пити",	L"пијен",	глаг, прид, { прел } },
{ L"радити",L"рађен",	глаг, прид, { прел } },
{ L"хтети",	L"",		глаг, прид, { прел } },
{ L"имати",	L"",		глаг, прид, { прел } },
{ L"немати",L"",		глаг, прид, { прел } },
{ L"чути",	L"",		глаг, прид, { прел } },

	// Придев->Прилог:
{ L"*",		L"*о",		прид, прил },	//брзо, лепо
{ L"*ак",	L"*ко",		прид, прил },	//кратак
{ L"*ан",	L"*но",		прид, прил },	//паметан
{ L"*и",	L"*о",		прид, прил },	//мали
{ L"јак",	L"јако",	прид, прил },

	// Заменица->Присвојни придев:
{ L"ја",	L"мој",		зам, прид },
{ L"ти",	L"твој",	зам, прид },
{ L"он",	L"његов",	зам, прид },
{ L"она",	L"њен",		зам, прид },
{ L"оно",	L"његов",	зам, прид },
{ L"ми",	L"наш",		зам, прид },
{ L"ви",	L"ваш",		зам, прид },
{ L"они",	L"њихов",	зам, прид },
{ L"оне",	L"њихов",	зам, прид },
	//{ L"она",	L"њихов",	зам, прид },	//Shadows "ona"

	// Именица->Присвојни придеви:
{ L"*",		L"*ов",		имен, прид },	//Миланов, Ненадов, монахов
{ L"*о",	L"*ов",		имен, прид },
{ L"коњ",	L"коњев",	имен, прид },
{ L"*а",	L"*ин",		имен, прид },		//женин
{ L"*це",	L"*чев",	имен, прид },	//сунце
{ L"*ао",	L"*лов",	имен, прид },	//орао, петао
{ L"*ац",	L"*чев",	имен, прид },	//старац
{ L"сто",	L"столов",	имен, прид },

	// Именица->Придев:
	//{ L"*а",	L"*ски",	имен, прид },	//жена, свиња : TODO: shadowed by *a -> *in
{ L"*еме",	L"*еменски",имен, прид },	//време, племе