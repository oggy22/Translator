#include "Languages\English.h"

const std::unordered_map<English::attributes, English::attribute_categories> English::belongs_to_category
{
	{ per1, attribute_categories::person },
	{ per2, attribute_categories::person },
	{ per3, attribute_categories::person },
};

const English::string_t English::stAlphabet("abcdefghijklmnopqrstuvwxyz");