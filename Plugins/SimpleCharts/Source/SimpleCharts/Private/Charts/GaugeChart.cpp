﻿// Copyright 2020 LHM. All Rights Reserved
#include "GaugeChart.h"

#define LOCTEXT_NAMESPACE "UMG"

UGaugeChart::UGaugeChart(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Series.name = "default";
	Series.data.Add(FGaugeData("1", 60.0f));
}

void UGaugeChart::OnLoadCompleted()
{
	Super::OnLoadCompleted();
	SetSeries(Series);
	SetTitle(title_text, title_show, title_position, title_fontSize, title_color);
	//SetLegend(legend_show, legend_position, legend_orient, legend_color, legend_fontSize);
	SetTooltipStyle(tooltip_trigger, tooltip_type,text_color,tip_backgroundColor);
	UpdateChart();
}

void UGaugeChart::SynchronizeProperties()
{
	Super::SynchronizeProperties();
		SetSeries(Series);
		SetTitle(title_text, title_show, title_position, title_fontSize, title_color);
		//SetLegend(legend_show, legend_position, legend_orient, legend_color, legend_fontSize);
		SetTooltipStyle(tooltip_trigger, tooltip_type,text_color,tip_backgroundColor);
		UpdateChart();
}

#if WITH_EDITOR
const FText UGaugeChart::GetPaletteCategory()
{
	return LOCTEXT("Chart", "SimpleChart");
}
#endif

void UGaugeChart::SetLegend(bool show, Position position, Orient orient, FLinearColor color, int32 fontSize)
{
	legend_show = show;
	legend_position = position;
	legend_orient = orient;
	legend_color = color.ToFColor(true);
	legend_fontSize = fontSize;
	if (!legend_json.IsValid())
	{
		legend_json = MakeShareable(new FJsonObject);
	}
	//legend setting
	legend_json->SetBoolField(TEXT("show"), legend_show);
	if (legend_show)
	{
		switch (legend_position)
		{
		case Position::center:
			legend_json->SetStringField(TEXT("x"), "center");
			break;
		case Position::left:
			legend_json->SetStringField(TEXT("x"), "left");
			break;
		case Position::right:
			legend_json->SetStringField(TEXT("x"), "right");
			break;
		default:
			break;
		}
		switch (legend_orient)
		{
		case Orient::horizontal:
			legend_json->SetStringField(TEXT("orient"), "horizontal");
			break;
		case Orient::vertical:
			legend_json->SetStringField(TEXT("orient"), "vertical");
			break;
		default:
			break;
		}
		TArray<TSharedPtr<FJsonValue>> legend_data;
		//for (auto d : Series)
		//{
		//	legend_data.Add(MakeShareable(new FJsonValueString(d.name)));
		//}
		legend_json->SetArrayField(TEXT("data"), legend_data);
		TSharedPtr<FJsonObject> legend_textStyle = MakeShareable(new FJsonObject);;
		legend_textStyle->SetNumberField(TEXT("fontSize"), legend_fontSize);
		legend_textStyle->SetStringField(TEXT("color"), ColorToRGBA(legend_color));
		legend_json->SetObjectField(TEXT("textStyle"), legend_textStyle);
	}
	if (!options_json.IsValid())
	{
		options_json = MakeShareable(new FJsonObject);
	}
	options_json->SetObjectField(TEXT("legend"), legend_json);
	//UpdateChart();
}

void UGaugeChart::SetSeries(FGaugeSeries SeriesData)
{
	Series = SeriesData;
	//Series setting
	series_json.Reset();
	TSharedPtr<FJsonObject> temp = MakeShareable(new FJsonObject);
	temp->SetStringField(TEXT("name"), Series.name);
	temp->SetStringField(TEXT("type"), TEXT("gauge"));
	temp->SetNumberField(TEXT("min"), Series.min);
	temp->SetNumberField(TEXT("max"), Series.max);

	TArray<TSharedPtr<FJsonValue>> tempdata;
	for (auto v : Series.data)
	{
		TSharedPtr<FJsonObject> data = MakeShareable(new FJsonObject);
		data->SetNumberField(TEXT("value"), v.value);
		data->SetStringField(TEXT("name"), v.name);
		tempdata.Add(MakeShareable(new FJsonValueObject(data)));
	}
	temp->SetArrayField(TEXT("data"), tempdata);
	series_json.Add(MakeShareable(new FJsonValueObject(temp)));
	if (!options_json.IsValid())
	{
		options_json = MakeShareable(new FJsonObject);
	}
	options_json->SetArrayField(TEXT("series"), series_json);
	SetLegend(legend_show, legend_position, legend_orient, legend_color, legend_fontSize);
	//UpdateChart();
}
#undef LOCTEXT_NAMESPACE
