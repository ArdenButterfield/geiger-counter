#pragma once
#include <juce_core/juce_core.h>
enum PARAM {
	RADIATION,
	FREQUENCY,
	SPEAKER,
	ROOM,
	GAIN,
	TOTAL_NUMBER_PARAMETERS
};
static const std::array<juce::Identifier, PARAM::TOTAL_NUMBER_PARAMETERS> PARAMETER_IDS{
	"RADIATION",
	"FREQUENCY",
	"SPEAKER",
	"ROOM",
	"GAIN",
};
static const std::array<juce::String, PARAM::TOTAL_NUMBER_PARAMETERS> PARAMETER_NAMES{
	"RADIATION",
	"FREQUENCY",
	"SPEAKER",
	"ROOM",
	"GAIN",
};
static const std::array<juce::NormalisableRange<float>, PARAM::TOTAL_NUMBER_PARAMETERS> PARAMETER_RANGES {
	juce::NormalisableRange<float>(0.0f, 100.0f, 0.0f, 1.0f),
	juce::NormalisableRange<float>(1.0f, 4.0f, 0.0f, 1.0f),
	juce::NormalisableRange<float>(0.0f, 100.0f, 0.0f, 1.0f),
	juce::NormalisableRange<float>(0.0f, 100.0f, 0.0f, 1.0f),
	juce::NormalisableRange<float>(0.0f, 100.0f, 0.0f, 1.0f),
};
static const std::array<float, PARAM::TOTAL_NUMBER_PARAMETERS> PARAMETER_DEFAULTS {
	50.0f,
	3.0f,
	50.0f,
	50.0f,
	50.0f,
};
static const std::array<bool, PARAM::TOTAL_NUMBER_PARAMETERS> PARAMETER_AUTOMATABLE {
	true,
	true,
	true,
	true,
	true,
};
static const std::array<juce::String, PARAM::TOTAL_NUMBER_PARAMETERS> PARAMETER_NICKNAMES{
	"Radiation",
	"Frequency",
	"Speaker",
	"Room",
	"Gain",
};
static const std::array<juce::String, PARAM::TOTAL_NUMBER_PARAMETERS> PARAMETER_SUFFIXES {
	"%",
	"kHz",
	"%",
	"%",
	"%",
};
static const std::array<juce::String, PARAM::TOTAL_NUMBER_PARAMETERS> PARAMETER_TOOLTIPS {
	"Radiation Parameter",
	"Frequency Parameter",
	"Speaker Parameter",
	"Room Parameter",
	"Loudness Parameter",
};
static const std::array<std::vector<juce::String>, PARAM::TOTAL_NUMBER_PARAMETERS> PARAMETER_TO_STRING_ARRS {
	std::vector<juce::String>{
	},
	std::vector<juce::String>{
	},
	std::vector<juce::String>{
	},
	std::vector<juce::String>{
	},
	std::vector<juce::String>{
	},
};