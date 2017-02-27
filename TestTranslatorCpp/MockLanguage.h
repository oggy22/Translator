#pragma once

class MockLanguage : translator::Language<MockLanguage, wchar_t>
{
public:
	enum class attributes
	{
		per1, per2, per3,
		sing, plur,
		nom, gen, dat, accus,
		negative
	};

	enum class attribute_categories
	{
		person, plurality, gcase
	};

	static const map<MockLanguage::attributes, MockLanguage::attribute_categories> belongs_to_category;
};

const map<MockLanguage::attributes, MockLanguage::attribute_categories> MockLanguage::belongs_to_category
{
	{ attributes::per1, attribute_categories::person },
	{ attributes::per2, attribute_categories::person },
	{ attributes::per3, attribute_categories::person },
	{ attributes::sing, attribute_categories::plurality },
	{ attributes::plur, attribute_categories::plurality },
	{ attributes::nom, attribute_categories::gcase },
	{ attributes::gen, attribute_categories::gcase },
	{ attributes::dat, attribute_categories::gcase },
	{ attributes::accus, attribute_categories::gcase },
};