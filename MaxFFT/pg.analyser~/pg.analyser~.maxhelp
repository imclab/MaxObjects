{
	"patcher" : 	{
		"fileversion" : 1,
		"rect" : [ 97.0, 63.0, 925.0, 658.0 ],
		"bglocked" : 0,
		"defrect" : [ 97.0, 63.0, 925.0, 658.0 ],
		"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
		"openinpresentation" : 0,
		"default_fontsize" : 11.595187,
		"default_fontface" : 0,
		"default_fontname" : "Arial",
		"gridonopen" : 0,
		"gridsize" : [ 15.0, 15.0 ],
		"gridsnaponopen" : 0,
		"toolbarvisible" : 1,
		"boxanimatetime" : 200,
		"imprint" : 0,
		"enablehscroll" : 1,
		"enablevscroll" : 1,
		"devicewidth" : 0.0,
		"boxes" : [ 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Adc~",
					"id" : "obj-20",
					"patching_rect" : [ 795.0, 165.0, 38.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p noisy",
					"id" : "obj-24",
					"patching_rect" : [ 435.0, 270.0, 47.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"fontname" : "Arial",
					"patcher" : 					{
						"fileversion" : 1,
						"rect" : [ 0.0, 0.0, 640.0, 480.0 ],
						"bglocked" : 0,
						"defrect" : [ 0.0, 0.0, 640.0, 480.0 ],
						"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
						"openinpresentation" : 0,
						"default_fontsize" : 12.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 0,
						"gridsize" : [ 15.0, 15.0 ],
						"gridsnaponopen" : 0,
						"toolbarvisible" : 1,
						"boxanimatetime" : 200,
						"imprint" : 0,
						"enablehscroll" : 1,
						"enablevscroll" : 1,
						"devicewidth" : 0.0,
						"boxes" : [ 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "noise~",
									"id" : "obj-68",
									"patching_rect" : [ 50.0, 100.0, 43.0, 20.0 ],
									"numinlets" : 1,
									"fontsize" : 11.595187,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "biquad~",
									"id" : "obj-69",
									"patching_rect" : [ 215.0, 130.0, 79.0, 20.0 ],
									"numinlets" : 6,
									"fontsize" : 11.595187,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"id" : "obj-16",
									"patching_rect" : [ 227.0, 40.0, 25.0, 25.0 ],
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "list" ],
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"id" : "obj-20",
									"patching_rect" : [ 215.0, 210.0, 25.0, 25.0 ],
									"numinlets" : 1,
									"numoutlets" : 0,
									"comment" : ""
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-69", 0 ],
									"destination" : [ "obj-20", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-16", 0 ],
									"destination" : [ "obj-69", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-68", 0 ],
									"destination" : [ "obj-69", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"fontface" : 0,
						"fontsize" : 12.0,
						"globalpatchername" : "",
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"default_fontsize" : 12.0,
						"fontname" : "Arial"
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Kurtosis",
					"id" : "obj-116",
					"patching_rect" : [ 317.0, 407.0, 63.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"textcolor" : [ 0.654902, 0.0, 0.654902, 1.0 ],
					"numoutlets" : 0,
					"frgb" : [ 0.654902, 0.0, 0.654902, 1.0 ],
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Skewnes",
					"id" : "obj-115",
					"patching_rect" : [ 242.0, 407.0, 63.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"textcolor" : [ 0.0, 0.0, 1.0, 1.0 ],
					"numoutlets" : 0,
					"frgb" : [ 0.0, 0.0, 1.0, 1.0 ],
					"bgcolor" : [ 0.0, 0.0, 1.0, 0.0 ],
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Spread",
					"id" : "obj-114",
					"patching_rect" : [ 165.0, 405.0, 55.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"textcolor" : [ 0.0, 1.0, 0.0, 1.0 ],
					"numoutlets" : 0,
					"frgb" : [ 0.0, 1.0, 0.0, 1.0 ],
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Centroid",
					"id" : "obj-113",
					"patching_rect" : [ 92.0, 407.0, 55.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"textcolor" : [ 1.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 0,
					"frgb" : [ 1.0, 0.0, 0.0, 1.0 ],
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "The hanning function seems to be the best.",
					"linecount" : 4,
					"id" : "obj-110",
					"patching_rect" : [ 744.0, 448.0, 81.0, 60.0 ],
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p display",
					"id" : "obj-109",
					"patching_rect" : [ 120.0, 465.0, 238.0, 20.0 ],
					"numinlets" : 4,
					"fontsize" : 11.595187,
					"numoutlets" : 5,
					"outlettype" : [ "", "float", "", "float", "" ],
					"fontname" : "Arial",
					"patcher" : 					{
						"fileversion" : 1,
						"rect" : [ 553.0, 125.0, 640.0, 480.0 ],
						"bglocked" : 0,
						"defrect" : [ 553.0, 125.0, 640.0, 480.0 ],
						"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
						"openinpresentation" : 0,
						"default_fontsize" : 12.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 0,
						"gridsize" : [ 15.0, 15.0 ],
						"gridsnaponopen" : 0,
						"toolbarvisible" : 1,
						"boxanimatetime" : 200,
						"imprint" : 0,
						"enablehscroll" : 1,
						"enablevscroll" : 1,
						"devicewidth" : 0.0,
						"boxes" : [ 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "p draw_lcd2",
									"id" : "obj-98",
									"patching_rect" : [ 335.0, 130.0, 73.0, 20.0 ],
									"numinlets" : 2,
									"fontsize" : 11.595187,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"fontname" : "Arial",
									"patcher" : 									{
										"fileversion" : 1,
										"rect" : [ 402.0, 142.0, 640.0, 480.0 ],
										"bglocked" : 0,
										"defrect" : [ 402.0, 142.0, 640.0, 480.0 ],
										"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
										"openinpresentation" : 0,
										"default_fontsize" : 12.0,
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"gridonopen" : 0,
										"gridsize" : [ 15.0, 15.0 ],
										"gridsnaponopen" : 0,
										"toolbarvisible" : 1,
										"boxanimatetime" : 200,
										"imprint" : 0,
										"enablehscroll" : 1,
										"enablevscroll" : 1,
										"devicewidth" : 0.0,
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "+ 12.",
													"id" : "obj-3",
													"patching_rect" : [ 58.0, 268.0, 38.0, 20.0 ],
													"numinlets" : 2,
													"fontsize" : 12.0,
													"numoutlets" : 1,
													"outlettype" : [ "float" ],
													"fontname" : "Arial"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "flonum",
													"id" : "obj-2",
													"patching_rect" : [ 280.0, 241.0, 50.0, 20.0 ],
													"numinlets" : 1,
													"fontsize" : 12.0,
													"numoutlets" : 2,
													"outlettype" : [ "float", "bang" ],
													"fontname" : "Arial"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "+",
													"id" : "obj-34",
													"patching_rect" : [ 155.0, 273.0, 32.5, 20.0 ],
													"numinlets" : 2,
													"fontsize" : 12.0,
													"numoutlets" : 1,
													"outlettype" : [ "int" ],
													"fontname" : "Arial"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "-",
													"id" : "obj-33",
													"patching_rect" : [ 101.0, 276.0, 32.5, 20.0 ],
													"numinlets" : 2,
													"fontsize" : 12.0,
													"numoutlets" : 1,
													"outlettype" : [ "int" ],
													"fontname" : "Arial"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "!- 150.",
													"id" : "obj-32",
													"patching_rect" : [ 44.0, 194.0, 43.0, 20.0 ],
													"numinlets" : 2,
													"fontsize" : 11.595187,
													"numoutlets" : 1,
													"outlettype" : [ "float" ],
													"fontname" : "Arial"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "flonum",
													"id" : "obj-31",
													"patching_rect" : [ 44.0, 238.0, 50.0, 20.0 ],
													"numinlets" : 1,
													"fontsize" : 12.0,
													"numoutlets" : 2,
													"outlettype" : [ "float", "bang" ],
													"fontname" : "Arial"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "flonum",
													"id" : "obj-24",
													"patching_rect" : [ 121.0, 197.0, 50.0, 20.0 ],
													"numinlets" : 1,
													"fontsize" : 12.0,
													"numoutlets" : 2,
													"outlettype" : [ "float", "bang" ],
													"fontname" : "Arial"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "scale 0 22050 0 300",
													"id" : "obj-22",
													"patching_rect" : [ 262.0, 165.0, 119.0, 20.0 ],
													"numinlets" : 6,
													"fontsize" : 12.0,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"fontname" : "Arial"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "flonum",
													"id" : "obj-21",
													"patching_rect" : [ 257.0, 121.0, 50.0, 20.0 ],
													"numinlets" : 1,
													"fontsize" : 12.0,
													"numoutlets" : 2,
													"outlettype" : [ "float", "bang" ],
													"fontname" : "Arial"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"id" : "obj-18",
													"patching_rect" : [ 243.0, 54.0, 25.0, 25.0 ],
													"numinlets" : 0,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "minimum 150.",
													"id" : "obj-17",
													"patching_rect" : [ 77.0, 166.0, 86.0, 20.0 ],
													"numinlets" : 2,
													"fontsize" : 12.0,
													"numoutlets" : 2,
													"outlettype" : [ "float", "int" ],
													"fontname" : "Arial"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "* 50.",
													"id" : "obj-16",
													"patching_rect" : [ 77.0, 140.0, 35.0, 20.0 ],
													"numinlets" : 2,
													"fontsize" : 12.0,
													"numoutlets" : 1,
													"outlettype" : [ "float" ],
													"fontname" : "Arial"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "expr log10($f1)",
													"id" : "obj-26",
													"patching_rect" : [ 79.0, 108.5, 88.0, 20.0 ],
													"numinlets" : 1,
													"fontsize" : 11.595187,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"fontname" : "Arial"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "pack 0. 0.",
													"id" : "obj-54",
													"patching_rect" : [ 80.0, 304.0, 61.0, 20.0 ],
													"numinlets" : 2,
													"fontsize" : 11.595187,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"fontname" : "Arial"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "clear, pensize 2 2, frgb 166 0 166, framearc $1 50 $2 200 270 180",
													"id" : "obj-48",
													"patching_rect" : [ 83.0, 355.0, 350.0, 18.0 ],
													"numinlets" : 2,
													"fontsize" : 11.595187,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"fontname" : "Arial"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"id" : "obj-96",
													"patching_rect" : [ 80.0, 40.0, 25.0, 25.0 ],
													"numinlets" : 0,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"id" : "obj-97",
													"patching_rect" : [ 75.0, 409.0, 25.0, 25.0 ],
													"numinlets" : 1,
													"numoutlets" : 0,
													"comment" : ""
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-31", 0 ],
													"destination" : [ "obj-3", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-3", 0 ],
													"destination" : [ "obj-33", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-3", 0 ],
													"destination" : [ "obj-34", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-16", 0 ],
													"destination" : [ "obj-17", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-17", 0 ],
													"destination" : [ "obj-32", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-34", 0 ],
													"destination" : [ "obj-54", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-24", 0 ],
													"destination" : [ "obj-34", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-33", 0 ],
													"destination" : [ "obj-54", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-24", 0 ],
													"destination" : [ "obj-33", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-32", 0 ],
													"destination" : [ "obj-31", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-22", 0 ],
													"destination" : [ "obj-24", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-21", 0 ],
													"destination" : [ "obj-22", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-18", 0 ],
													"destination" : [ "obj-21", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-26", 0 ],
													"destination" : [ "obj-16", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-96", 0 ],
													"destination" : [ "obj-26", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-54", 0 ],
													"destination" : [ "obj-48", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-48", 0 ],
													"destination" : [ "obj-97", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-26", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}
,
									"saved_object_attributes" : 									{
										"fontface" : 0,
										"fontsize" : 12.0,
										"globalpatchername" : "",
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"default_fontsize" : 12.0,
										"fontname" : "Arial"
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "p filter",
									"id" : "obj-86",
									"patching_rect" : [ 335.0, 100.0, 42.0, 20.0 ],
									"numinlets" : 2,
									"fontsize" : 11.595187,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"fontname" : "Arial",
									"patcher" : 									{
										"fileversion" : 1,
										"rect" : [ 29.0, 67.0, 142.0, 130.0 ],
										"bglocked" : 0,
										"defrect" : [ 29.0, 67.0, 142.0, 130.0 ],
										"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
										"openinpresentation" : 0,
										"default_fontsize" : 12.0,
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"gridonopen" : 0,
										"gridsize" : [ 15.0, 15.0 ],
										"gridsnaponopen" : 0,
										"toolbarvisible" : 1,
										"boxanimatetime" : 200,
										"imprint" : 0,
										"enablehscroll" : 1,
										"enablevscroll" : 1,
										"devicewidth" : 0.0,
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "inlet",
													"id" : "obj-5",
													"patching_rect" : [ 75.0, 0.0, 25.0, 25.0 ],
													"numinlets" : 0,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"id" : "obj-4",
													"patching_rect" : [ 15.0, 105.0, 25.0, 25.0 ],
													"numinlets" : 1,
													"numoutlets" : 0,
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"id" : "obj-3",
													"patching_rect" : [ 15.0, 0.0, 25.0, 25.0 ],
													"numinlets" : 0,
													"numoutlets" : 1,
													"outlettype" : [ "float" ],
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "zl median 5",
													"id" : "obj-2",
													"patching_rect" : [ 15.0, 75.0, 79.0, 20.0 ],
													"numinlets" : 2,
													"fontsize" : 12.0,
													"numoutlets" : 2,
													"outlettype" : [ "", "" ],
													"fontname" : "Arial"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "zl stream 5",
													"id" : "obj-1",
													"patching_rect" : [ 14.0, 45.0, 69.0, 20.0 ],
													"numinlets" : 2,
													"fontsize" : 12.0,
													"numoutlets" : 2,
													"outlettype" : [ "", "" ],
													"fontname" : "Arial"
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-5", 0 ],
													"destination" : [ "obj-2", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-2", 0 ],
													"destination" : [ "obj-4", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-5", 0 ],
													"destination" : [ "obj-1", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-3", 0 ],
													"destination" : [ "obj-1", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-1", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}
,
									"saved_object_attributes" : 									{
										"fontface" : 0,
										"fontsize" : 12.0,
										"globalpatchername" : "",
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"default_fontsize" : 12.0,
										"fontname" : "Arial"
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "p filter",
									"id" : "obj-78",
									"patching_rect" : [ 215.0, 100.0, 42.0, 20.0 ],
									"numinlets" : 2,
									"fontsize" : 11.595187,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"fontname" : "Arial",
									"patcher" : 									{
										"fileversion" : 1,
										"rect" : [ 29.0, 67.0, 142.0, 130.0 ],
										"bglocked" : 0,
										"defrect" : [ 29.0, 67.0, 142.0, 130.0 ],
										"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
										"openinpresentation" : 0,
										"default_fontsize" : 12.0,
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"gridonopen" : 0,
										"gridsize" : [ 15.0, 15.0 ],
										"gridsnaponopen" : 0,
										"toolbarvisible" : 1,
										"boxanimatetime" : 200,
										"imprint" : 0,
										"enablehscroll" : 1,
										"enablevscroll" : 1,
										"devicewidth" : 0.0,
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "inlet",
													"id" : "obj-5",
													"patching_rect" : [ 75.0, 0.0, 25.0, 25.0 ],
													"numinlets" : 0,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"id" : "obj-4",
													"patching_rect" : [ 15.0, 105.0, 25.0, 25.0 ],
													"numinlets" : 1,
													"numoutlets" : 0,
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"id" : "obj-3",
													"patching_rect" : [ 15.0, 0.0, 25.0, 25.0 ],
													"numinlets" : 0,
													"numoutlets" : 1,
													"outlettype" : [ "float" ],
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "zl median 5",
													"id" : "obj-2",
													"patching_rect" : [ 15.0, 75.0, 79.0, 20.0 ],
													"numinlets" : 2,
													"fontsize" : 12.0,
													"numoutlets" : 2,
													"outlettype" : [ "", "" ],
													"fontname" : "Arial"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "zl stream 5",
													"id" : "obj-1",
													"patching_rect" : [ 14.0, 45.0, 69.0, 20.0 ],
													"numinlets" : 2,
													"fontsize" : 12.0,
													"numoutlets" : 2,
													"outlettype" : [ "", "" ],
													"fontname" : "Arial"
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-1", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-3", 0 ],
													"destination" : [ "obj-1", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-5", 0 ],
													"destination" : [ "obj-1", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-2", 0 ],
													"destination" : [ "obj-4", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-5", 0 ],
													"destination" : [ "obj-2", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}
,
									"saved_object_attributes" : 									{
										"fontface" : 0,
										"fontsize" : 12.0,
										"globalpatchername" : "",
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"default_fontsize" : 12.0,
										"fontname" : "Arial"
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "p filter",
									"id" : "obj-76",
									"patching_rect" : [ 125.0, 100.0, 42.0, 20.0 ],
									"numinlets" : 2,
									"fontsize" : 11.595187,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"fontname" : "Arial",
									"patcher" : 									{
										"fileversion" : 1,
										"rect" : [ 29.0, 67.0, 142.0, 130.0 ],
										"bglocked" : 0,
										"defrect" : [ 29.0, 67.0, 142.0, 130.0 ],
										"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
										"openinpresentation" : 0,
										"default_fontsize" : 12.0,
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"gridonopen" : 0,
										"gridsize" : [ 15.0, 15.0 ],
										"gridsnaponopen" : 0,
										"toolbarvisible" : 1,
										"boxanimatetime" : 200,
										"imprint" : 0,
										"enablehscroll" : 1,
										"enablevscroll" : 1,
										"devicewidth" : 0.0,
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "inlet",
													"id" : "obj-5",
													"patching_rect" : [ 75.0, 0.0, 25.0, 25.0 ],
													"numinlets" : 0,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"id" : "obj-4",
													"patching_rect" : [ 15.0, 105.0, 25.0, 25.0 ],
													"numinlets" : 1,
													"numoutlets" : 0,
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"id" : "obj-3",
													"patching_rect" : [ 15.0, 0.0, 25.0, 25.0 ],
													"numinlets" : 0,
													"numoutlets" : 1,
													"outlettype" : [ "float" ],
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "zl median 5",
													"id" : "obj-2",
													"patching_rect" : [ 15.0, 75.0, 79.0, 20.0 ],
													"numinlets" : 2,
													"fontsize" : 12.0,
													"numoutlets" : 2,
													"outlettype" : [ "", "" ],
													"fontname" : "Arial"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "zl stream 5",
													"id" : "obj-1",
													"patching_rect" : [ 14.0, 45.0, 69.0, 20.0 ],
													"numinlets" : 2,
													"fontsize" : 12.0,
													"numoutlets" : 2,
													"outlettype" : [ "", "" ],
													"fontname" : "Arial"
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-5", 0 ],
													"destination" : [ "obj-2", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-2", 0 ],
													"destination" : [ "obj-4", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-5", 0 ],
													"destination" : [ "obj-1", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-3", 0 ],
													"destination" : [ "obj-1", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-1", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}
,
									"saved_object_attributes" : 									{
										"fontface" : 0,
										"fontsize" : 12.0,
										"globalpatchername" : "",
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"default_fontsize" : 12.0,
										"fontname" : "Arial"
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "p filter",
									"id" : "obj-26",
									"patching_rect" : [ 50.0, 100.0, 42.0, 20.0 ],
									"numinlets" : 2,
									"fontsize" : 11.595187,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"fontname" : "Arial",
									"patcher" : 									{
										"fileversion" : 1,
										"rect" : [ 29.0, 67.0, 142.0, 130.0 ],
										"bglocked" : 0,
										"defrect" : [ 29.0, 67.0, 142.0, 130.0 ],
										"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
										"openinpresentation" : 0,
										"default_fontsize" : 12.0,
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"gridonopen" : 0,
										"gridsize" : [ 15.0, 15.0 ],
										"gridsnaponopen" : 0,
										"toolbarvisible" : 1,
										"boxanimatetime" : 200,
										"imprint" : 0,
										"enablehscroll" : 1,
										"enablevscroll" : 1,
										"devicewidth" : 0.0,
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "inlet",
													"id" : "obj-5",
													"patching_rect" : [ 75.0, 0.0, 25.0, 25.0 ],
													"numinlets" : 0,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"id" : "obj-4",
													"patching_rect" : [ 15.0, 105.0, 25.0, 25.0 ],
													"numinlets" : 1,
													"numoutlets" : 0,
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"id" : "obj-3",
													"patching_rect" : [ 15.0, 0.0, 25.0, 25.0 ],
													"numinlets" : 0,
													"numoutlets" : 1,
													"outlettype" : [ "float" ],
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "zl median 5",
													"id" : "obj-2",
													"patching_rect" : [ 15.0, 75.0, 79.0, 20.0 ],
													"numinlets" : 2,
													"fontsize" : 12.0,
													"numoutlets" : 2,
													"outlettype" : [ "", "" ],
													"fontname" : "Arial"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "zl stream 5",
													"id" : "obj-1",
													"patching_rect" : [ 14.0, 45.0, 69.0, 20.0 ],
													"numinlets" : 2,
													"fontsize" : 12.0,
													"numoutlets" : 2,
													"outlettype" : [ "", "" ],
													"fontname" : "Arial"
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-1", 0 ],
													"destination" : [ "obj-2", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-3", 0 ],
													"destination" : [ "obj-1", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-5", 0 ],
													"destination" : [ "obj-1", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-2", 0 ],
													"destination" : [ "obj-4", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-5", 0 ],
													"destination" : [ "obj-2", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}
,
									"saved_object_attributes" : 									{
										"fontface" : 0,
										"fontsize" : 12.0,
										"globalpatchername" : "",
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"default_fontsize" : 12.0,
										"fontname" : "Arial"
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "p draw_lcd",
									"id" : "obj-57",
									"patching_rect" : [ 215.0, 130.0, 67.0, 20.0 ],
									"numinlets" : 1,
									"fontsize" : 11.59518,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"fontname" : "Arial",
									"patcher" : 									{
										"fileversion" : 1,
										"rect" : [ 364.0, 58.0, 763.0, 604.0 ],
										"bglocked" : 0,
										"defrect" : [ 364.0, 58.0, 763.0, 604.0 ],
										"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
										"openinpresentation" : 0,
										"default_fontsize" : 18.0,
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"gridonopen" : 0,
										"gridsize" : [ 15.0, 15.0 ],
										"gridsnaponopen" : 0,
										"toolbarvisible" : 1,
										"boxanimatetime" : 200,
										"imprint" : 0,
										"enablehscroll" : 1,
										"enablevscroll" : 1,
										"devicewidth" : 0.0,
										"boxes" : [ 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "* 0.05",
													"id" : "obj-45",
													"patching_rect" : [ 31.0, 46.0, 43.0, 20.0 ],
													"numinlets" : 2,
													"fontsize" : 12.0,
													"numoutlets" : 1,
													"outlettype" : [ "float" ],
													"fontname" : "Arial"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"id" : "obj-44",
													"patching_rect" : [ 31.0, 11.0, 25.0, 25.0 ],
													"numinlets" : 0,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "+ 50",
													"id" : "obj-43",
													"patching_rect" : [ 480.0, 424.0, 35.0, 20.0 ],
													"numinlets" : 2,
													"fontsize" : 12.0,
													"numoutlets" : 1,
													"outlettype" : [ "int" ],
													"fontname" : "Arial"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "+ 130",
													"id" : "obj-42",
													"patching_rect" : [ 330.0, 423.0, 42.0, 20.0 ],
													"numinlets" : 2,
													"fontsize" : 12.0,
													"numoutlets" : 1,
													"outlettype" : [ "int" ],
													"fontname" : "Arial"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "+ 50",
													"id" : "obj-41",
													"patching_rect" : [ 181.0, 425.0, 35.0, 20.0 ],
													"numinlets" : 2,
													"fontsize" : 12.0,
													"numoutlets" : 1,
													"outlettype" : [ "int" ],
													"fontname" : "Arial"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "+ 130",
													"id" : "obj-40",
													"patching_rect" : [ 31.0, 424.0, 42.0, 20.0 ],
													"numinlets" : 2,
													"fontsize" : 12.0,
													"numoutlets" : 1,
													"outlettype" : [ "int" ],
													"fontname" : "Arial"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "pack 0. 0. 0. 0.",
													"id" : "obj-39",
													"patching_rect" : [ 31.0, 454.0, 468.0, 20.0 ],
													"numinlets" : 4,
													"fontsize" : 12.0,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"fontname" : "Arial"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "t f f f f",
													"id" : "obj-34",
													"patching_rect" : [ 31.0, 126.0, 59.5, 20.0 ],
													"numinlets" : 1,
													"fontsize" : 12.0,
													"numoutlets" : 4,
													"outlettype" : [ "float", "float", "float", "float" ],
													"fontname" : "Arial"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "expr 250.* sin($f1)",
													"id" : "obj-31",
													"patching_rect" : [ 480.0, 315.0, 109.0, 20.0 ],
													"numinlets" : 1,
													"fontsize" : 12.0,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"fontname" : "Arial"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "expr -150. * sin($f1)",
													"id" : "obj-26",
													"patching_rect" : [ 181.0, 315.0, 116.0, 20.0 ],
													"numinlets" : 1,
													"fontsize" : 12.0,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"fontname" : "Arial"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "expr 250.* cos($f1)",
													"id" : "obj-24",
													"patching_rect" : [ 330.0, 315.0, 112.0, 20.0 ],
													"numinlets" : 1,
													"fontsize" : 12.0,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"fontname" : "Arial"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "expr -150.* cos($f1)",
													"id" : "obj-12",
													"patching_rect" : [ 31.0, 315.0, 116.0, 20.0 ],
													"numinlets" : 1,
													"fontsize" : 12.0,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"fontname" : "Arial"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "% 3.141593",
													"id" : "obj-3",
													"patching_rect" : [ 31.0, 99.0, 76.0, 20.0 ],
													"numinlets" : 2,
													"fontsize" : 12.0,
													"numoutlets" : 1,
													"outlettype" : [ "int" ],
													"fontname" : "Arial"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"id" : "obj-58",
													"patching_rect" : [ 31.0, 562.0, 25.0, 25.0 ],
													"numinlets" : 1,
													"numoutlets" : 0,
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "recordsprite, pensize 2 2, frgb 0 0 255, linesegment $1 $2 $3 $4, closesprite line, drawsprite line 0 0",
													"id" : "obj-5",
													"patching_rect" : [ 31.0, 487.0, 541.0, 18.0 ],
													"numinlets" : 2,
													"fontsize" : 12.0,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"fontname" : "Arial"
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-34", 3 ],
													"destination" : [ "obj-31", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-34", 2 ],
													"destination" : [ "obj-24", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-34", 1 ],
													"destination" : [ "obj-26", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-3", 0 ],
													"destination" : [ "obj-34", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-34", 0 ],
													"destination" : [ "obj-12", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-31", 0 ],
													"destination" : [ "obj-43", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-24", 0 ],
													"destination" : [ "obj-42", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-26", 0 ],
													"destination" : [ "obj-41", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-12", 0 ],
													"destination" : [ "obj-40", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-44", 0 ],
													"destination" : [ "obj-45", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-43", 0 ],
													"destination" : [ "obj-39", 3 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-41", 0 ],
													"destination" : [ "obj-39", 1 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-42", 0 ],
													"destination" : [ "obj-39", 2 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-40", 0 ],
													"destination" : [ "obj-39", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-5", 0 ],
													"destination" : [ "obj-58", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-39", 0 ],
													"destination" : [ "obj-5", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-45", 0 ],
													"destination" : [ "obj-3", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}
,
									"saved_object_attributes" : 									{
										"fontface" : 0,
										"fontsize" : 18.0,
										"globalpatchername" : "",
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"default_fontsize" : 18.0,
										"fontname" : "Arial"
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "+ 0.",
									"id" : "obj-45",
									"patching_rect" : [ 290.0, 145.0, 32.5, 20.0 ],
									"numinlets" : 2,
									"fontsize" : 11.595187,
									"numoutlets" : 1,
									"outlettype" : [ "float" ],
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "- 0.",
									"id" : "obj-44",
									"patching_rect" : [ 80.0, 145.0, 32.5, 20.0 ],
									"numinlets" : 2,
									"fontsize" : 11.595187,
									"numoutlets" : 1,
									"outlettype" : [ "float" ],
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"id" : "obj-99",
									"patching_rect" : [ 50.0, 40.0, 25.0, 25.0 ],
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "float" ],
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"id" : "obj-101",
									"patching_rect" : [ 125.0, 40.0, 25.0, 25.0 ],
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "float" ],
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"id" : "obj-102",
									"patching_rect" : [ 215.0, 40.0, 25.0, 25.0 ],
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "float" ],
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"id" : "obj-103",
									"patching_rect" : [ 335.0, 40.0, 25.0, 25.0 ],
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "float" ],
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"id" : "obj-104",
									"patching_rect" : [ 50.0, 225.0, 25.0, 25.0 ],
									"numinlets" : 1,
									"numoutlets" : 0,
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"id" : "obj-105",
									"patching_rect" : [ 80.0, 225.0, 25.0, 25.0 ],
									"numinlets" : 1,
									"numoutlets" : 0,
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"id" : "obj-106",
									"patching_rect" : [ 215.0, 225.0, 25.0, 25.0 ],
									"numinlets" : 1,
									"numoutlets" : 0,
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"id" : "obj-107",
									"patching_rect" : [ 290.0, 225.0, 25.0, 25.0 ],
									"numinlets" : 1,
									"numoutlets" : 0,
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"id" : "obj-108",
									"patching_rect" : [ 335.0, 225.0, 25.0, 25.0 ],
									"numinlets" : 1,
									"numoutlets" : 0,
									"comment" : ""
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-98", 0 ],
									"destination" : [ "obj-108", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-45", 0 ],
									"destination" : [ "obj-107", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-57", 0 ],
									"destination" : [ "obj-106", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-44", 0 ],
									"destination" : [ "obj-105", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-26", 0 ],
									"destination" : [ "obj-104", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-103", 0 ],
									"destination" : [ "obj-86", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-102", 0 ],
									"destination" : [ "obj-78", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-101", 0 ],
									"destination" : [ "obj-76", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-99", 0 ],
									"destination" : [ "obj-26", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-26", 0 ],
									"destination" : [ "obj-98", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-86", 0 ],
									"destination" : [ "obj-98", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-78", 0 ],
									"destination" : [ "obj-57", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-76", 0 ],
									"destination" : [ "obj-45", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-76", 0 ],
									"destination" : [ "obj-44", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-26", 0 ],
									"destination" : [ "obj-44", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-26", 0 ],
									"destination" : [ "obj-45", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"fontface" : 0,
						"fontsize" : 12.0,
						"globalpatchername" : "",
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"default_fontsize" : 12.0,
						"fontname" : "Arial"
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "lcd",
					"id" : "obj-39",
					"patching_rect" : [ 75.0, 510.0, 300.0, 100.0 ],
					"numinlets" : 1,
					"ignoreclick" : 1,
					"numoutlets" : 4,
					"outlettype" : [ "list", "list", "int", "" ],
					"bgtransparent" : 1,
					"border" : 0,
					"enablesprites" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "multislider",
					"thickness" : 3,
					"id" : "obj-18",
					"patching_rect" : [ 75.0, 510.0, 300.0, 100.0 ],
					"numinlets" : 1,
					"border_right" : 0,
					"ignoreclick" : 1,
					"slidercolor" : [ 1.0, 0.0, 0.0, 1.0 ],
					"numoutlets" : 2,
					"setminmax" : [ 0.0, 22050.0 ],
					"orientation" : 0,
					"outlettype" : [ "", "" ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"border_top" : 0,
					"border_bottom" : 0,
					"border_left" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "lcd",
					"id" : "obj-19",
					"patching_rect" : [ 75.0, 510.0, 300.0, 100.0 ],
					"numinlets" : 1,
					"ignoreclick" : 1,
					"numoutlets" : 4,
					"outlettype" : [ "list", "list", "int", "" ],
					"bgtransparent" : 1,
					"border" : 0,
					"enablesprites" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "rslider",
					"size" : 22051.0,
					"id" : "obj-15",
					"patching_rect" : [ 72.0, 509.0, 300.0, 103.0 ],
					"numinlets" : 2,
					"ignoreclick" : 1,
					"numoutlets" : 2,
					"bordercolor" : [ 0.85098, 0.533333, 0.254902, 0.0 ],
					"outlettype" : [ "", "" ],
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"fgcolor" : [ 0.0, 1.0, 0.0, 0.647059 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "number~",
					"id" : "obj-30",
					"patching_rect" : [ 300.0, 435.0, 58.0, 20.0 ],
					"numinlets" : 2,
					"sig" : 0.0,
					"fontsize" : 11.595187,
					"numoutlets" : 2,
					"outlettype" : [ "signal", "float" ],
					"mode" : 2,
					"fontname" : "Arial",
					"bgcolor2" : [ 0.654902, 0.0, 0.654902, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "number~",
					"id" : "obj-34",
					"patching_rect" : [ 225.0, 435.0, 60.0, 20.0 ],
					"numinlets" : 2,
					"sig" : 0.0,
					"fontsize" : 11.595187,
					"numoutlets" : 2,
					"outlettype" : [ "signal", "float" ],
					"mode" : 2,
					"fontname" : "Arial",
					"bgcolor2" : [ 0.0, 0.0, 1.0, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "number~",
					"id" : "obj-28",
					"patching_rect" : [ 150.0, 435.0, 62.0, 20.0 ],
					"numinlets" : 2,
					"sig" : 0.0,
					"fontsize" : 11.595187,
					"numoutlets" : 2,
					"outlettype" : [ "signal", "float" ],
					"mode" : 2,
					"fontname" : "Arial",
					"bgcolor2" : [ 0.0, 1.0, 0.0, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "loadmess 1",
					"id" : "obj-21",
					"patching_rect" : [ 624.0, 448.0, 70.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 1,
					"hidden" : 1,
					"outlettype" : [ "" ],
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Set the window type :",
					"id" : "obj-82",
					"patching_rect" : [ 615.0, 450.0, 121.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "umenu",
					"types" : [  ],
					"id" : "obj-77",
					"patching_rect" : [ 624.0, 478.0, 100.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 3,
					"outlettype" : [ "int", "", "" ],
					"items" : [ "Square", ",", "Hanning", ",", "Hamming", ",", "Turkey", ",", "Cosinus", ",", "Lancsoz", ",", "Triangular", ",", "Gaussian", ",", "Bartlett-Hann", ",", "Blackman", ",", "Kaizer", ",", "Nuttall", ",", "Blackman-Harris", ",", "Blackman-Nuttall", ",", "Flat-Top", ",", "Poisson" ],
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "window $1",
					"id" : "obj-71",
					"patching_rect" : [ 624.0, 508.0, 65.0, 18.0 ],
					"numinlets" : 2,
					"fontsize" : 11.595187,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "loadmess 440",
					"id" : "obj-84",
					"patching_rect" : [ 705.0, 165.0, 83.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 1,
					"hidden" : 1,
					"outlettype" : [ "" ],
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Set frequency",
					"id" : "obj-80",
					"patching_rect" : [ 690.0, 165.0, 83.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"id" : "obj-75",
					"patching_rect" : [ 705.0, 195.0, 58.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 2,
					"outlettype" : [ "float", "bang" ],
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "cycle~ 440",
					"id" : "obj-70",
					"patching_rect" : [ 705.0, 225.0, 66.0, 20.0 ],
					"numinlets" : 2,
					"fontsize" : 11.595187,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "ezadc~",
					"id" : "obj-79",
					"patching_rect" : [ 795.0, 195.0, 45.0, 45.0 ],
					"numinlets" : 1,
					"local" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "signal", "signal" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "loadmess 2",
					"id" : "obj-100",
					"patching_rect" : [ 75.0, 225.0, 70.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 1,
					"hidden" : 1,
					"outlettype" : [ "" ],
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Select source",
					"id" : "obj-42",
					"patching_rect" : [ 75.0, 225.0, 88.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Play with noise",
					"id" : "obj-25",
					"patching_rect" : [ 465.0, 150.0, 138.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Select an audio file",
					"linecount" : 2,
					"id" : "obj-40",
					"patching_rect" : [ 250.0, 144.0, 62.0, 33.0 ],
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "umenu",
					"types" : [  ],
					"id" : "obj-37",
					"patching_rect" : [ 75.0, 255.0, 88.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 3,
					"outlettype" : [ "int", "", "" ],
					"items" : [ "None", ",", "Audio", "file", ",", "Noise", ",", "Cycle~", ",", "Adc~" ],
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "selector~ 4",
					"id" : "obj-29",
					"patching_rect" : [ 75.0, 300.0, 739.0, 20.0 ],
					"numinlets" : 5,
					"fontsize" : 11.595187,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "umenu",
					"types" : [  ],
					"id" : "obj-47",
					"patching_rect" : [ 375.0, 150.0, 88.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 3,
					"outlettype" : [ "int", "", "" ],
					"items" : [ "display", ",", "lowpass", ",", "highpass", ",", "bandpass", ",", "bandstop", ",", "peaknotch", ",", "lowshelf", ",", "highshelf", ",", "resonant", ",", "allpass" ],
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "filtergraph~",
					"markercolor" : [ 0.509804, 0.509804, 0.509804, 1.0 ],
					"id" : "obj-81",
					"patching_rect" : [ 377.0, 182.0, 279.0, 77.0 ],
					"domain" : [ 0.0, 22050.0 ],
					"numinlets" : 8,
					"fontsize" : 8.998901,
					"numoutlets" : 7,
					"autoout" : 1,
					"outlettype" : [ "list", "float", "float", "float", "float", "list", "int" ],
					"bgcolor" : [ 0.913725, 0.913725, 1.0, 1.0 ],
					"logfreq" : 0,
					"hcurvecolor" : [ 1.0, 0.086275, 0.086275, 1.0 ],
					"bwidthcolor" : [ 0.462745, 0.47451, 0.65098, 1.0 ],
					"hbwidthcolor" : [ 0.823529, 0.290196, 0.211765, 1.0 ],
					"fgcolor" : [ 0.756863, 0.756863, 1.0, 1.0 ],
					"nfilters" : 1,
					"setfilter" : [ 0, 8, 0, 0, 0, 9958.064453, 1.0, 0.970266, 0.0001, 22050.0, 0.0001, 16.0, 0.5, 25.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "toggle",
					"id" : "obj-9",
					"patching_rect" : [ 225.0, 150.0, 20.0, 20.0 ],
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "int" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "toggle",
					"id" : "obj-8",
					"patching_rect" : [ 195.0, 150.0, 20.0, 20.0 ],
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "int" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "loop $1",
					"id" : "obj-7",
					"patching_rect" : [ 225.0, 180.0, 50.0, 18.0 ],
					"numinlets" : 2,
					"fontsize" : 12.0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "sfplay~ 2",
					"id" : "obj-6",
					"patching_rect" : [ 255.0, 240.0, 59.0, 20.0 ],
					"numinlets" : 2,
					"fontsize" : 12.0,
					"numoutlets" : 3,
					"outlettype" : [ "signal", "signal", "bang" ],
					"fontname" : "Arial",
					"save" : [ "#N", "sfplay~", "", 2, 120960, 0, "", ";" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "open",
					"id" : "obj-10",
					"patching_rect" : [ 135.0, 150.0, 37.0, 18.0 ],
					"numinlets" : 2,
					"fontsize" : 12.0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"id" : "obj-31",
					"patching_rect" : [ 360.0, 135.0, 318.0, 132.0 ],
					"numinlets" : 1,
					"numoutlets" : 0,
					"bgcolor" : [ 0.858824, 0.858824, 0.858824, 1.0 ],
					"border" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"id" : "obj-36",
					"patching_rect" : [ 120.0, 135.0, 210.0, 74.0 ],
					"numinlets" : 1,
					"numoutlets" : 0,
					"bgcolor" : [ 0.858824, 0.858824, 0.858824, 1.0 ],
					"border" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"id" : "obj-38",
					"patching_rect" : [ 60.0, 210.0, 111.0, 80.0 ],
					"numinlets" : 1,
					"numoutlets" : 0,
					"bgcolor" : [ 0.858824, 0.858824, 0.858824, 1.0 ],
					"border" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"id" : "obj-74",
					"patching_rect" : [ 690.0, 135.0, 86.0, 124.0 ],
					"numinlets" : 1,
					"numoutlets" : 0,
					"bgcolor" : [ 0.858824, 0.858824, 0.858824, 1.0 ],
					"border" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"id" : "obj-83",
					"patching_rect" : [ 780.0, 135.0, 80.0, 123.0 ],
					"numinlets" : 1,
					"numoutlets" : 0,
					"bgcolor" : [ 0.858824, 0.858824, 0.858824, 1.0 ],
					"border" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Pierre Guillot\nUniversite Paris 8",
					"linecount" : 2,
					"id" : "obj-59",
					"patching_rect" : [ 508.0, 13.0, 150.0, 33.0 ],
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "arg 3 : Window type",
					"id" : "obj-67",
					"patching_rect" : [ 615.0, 420.0, 150.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "gain~",
					"id" : "obj-23",
					"patching_rect" : [ 450.0, 420.0, 139.0, 21.0 ],
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "signal", "int" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s centroid",
					"id" : "obj-14",
					"patching_rect" : [ 624.0, 538.0, 61.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "r centroid",
					"id" : "obj-4",
					"patching_rect" : [ 15.0, 300.0, 59.0, 20.0 ],
					"numinlets" : 0,
					"fontsize" : 11.595187,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "number~",
					"id" : "obj-22",
					"patching_rect" : [ 75.0, 435.0, 64.0, 20.0 ],
					"numinlets" : 2,
					"sig" : 0.0,
					"fontsize" : 11.595187,
					"numoutlets" : 2,
					"outlettype" : [ "signal", "float" ],
					"mode" : 2,
					"fontname" : "Arial",
					"bgcolor2" : [ 1.0, 0.0, 0.0, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "-126dB",
					"linecount" : 2,
					"id" : "obj-49",
					"patching_rect" : [ 47.0, 587.0, 33.0, 33.0 ],
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "0dB",
					"id" : "obj-46",
					"patching_rect" : [ 47.0, 512.0, 38.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "22050Hz",
					"id" : "obj-35",
					"patching_rect" : [ 331.0, 617.0, 67.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "0Hz",
					"id" : "obj-32",
					"patching_rect" : [ 76.0, 617.0, 38.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "arg 2 : FFT overlapping",
					"id" : "obj-88",
					"patching_rect" : [ 615.0, 405.0, 137.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "arg 1 : FFT window size",
					"id" : "obj-87",
					"patching_rect" : [ 615.0, 390.0, 137.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Turn audio on",
					"linecount" : 3,
					"id" : "obj-43",
					"patching_rect" : [ 495.0, 465.0, 43.0, 46.0 ],
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Play with noise",
					"id" : "obj-41",
					"patching_rect" : [ 465.0, 150.0, 138.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "spectroscope~",
					"id" : "obj-12",
					"patching_rect" : [ 75.0, 510.0, 300.0, 100.0 ],
					"numinlets" : 2,
					"interval" : 10,
					"numoutlets" : 1,
					"curvecolor" : [ 0.145098, 0.07451, 0.376471, 1.0 ],
					"outlettype" : [ "" ],
					"fgcolor" : [ 0.239216, 0.643137, 0.709804, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "ezdac~",
					"id" : "obj-13",
					"patching_rect" : [ 450.0, 465.0, 45.0, 45.0 ],
					"numinlets" : 2,
					"local" : 1,
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "pg.analyser~ 2048 8 1",
					"id" : "obj-11",
					"patching_rect" : [ 75.0, 345.0, 244.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 4,
					"outlettype" : [ "", "", "", "" ],
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"varname" : "autohelp_top_title",
					"text" : "pg.analyser~",
					"id" : "obj-1",
					"patching_rect" : [ 8.0, 5.0, 485.0, 30.0 ],
					"numinlets" : 1,
					"fontface" : 3,
					"fontsize" : 20.871338,
					"textcolor" : [ 0.93, 0.93, 0.97, 1.0 ],
					"numoutlets" : 0,
					"frgb" : [ 0.93, 0.93, 0.97, 1.0 ],
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"varname" : "autohelp_top_digest",
					"text" : "Estimation of the centroid, the spread, the skewness and the kurtosis",
					"id" : "obj-2",
					"patching_rect" : [ 8.0, 34.0, 483.0, 21.0 ],
					"numinlets" : 1,
					"fontsize" : 12.754705,
					"textcolor" : [ 0.93, 0.93, 0.97, 1.0 ],
					"numoutlets" : 0,
					"frgb" : [ 0.93, 0.93, 0.97, 1.0 ],
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"varname" : "autohelp_top_description",
					"text" : "pg.centroid~ estimate the centroid, the spread, the skewness ond the kurtosis in the frequency domain.\nCentroid  indicates where is the center of mass of the spectrum and has a very nearly connection with the impression of brightness.\nSpread describes how far the spectrum is spread out around his spectral centroid.\nSkewness is a measure of the asymmetry of the spectrum around his spectral centroid.\nKurtosis is a measure of the flatness of the spectrum around his spectral centroid.",
					"linecount" : 5,
					"id" : "obj-3",
					"patching_rect" : [ 6.0, 55.0, 753.0, 73.0 ],
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"id" : "obj-17",
					"patching_rect" : [ 47.0, 497.0, 360.0, 150.0 ],
					"numinlets" : 1,
					"numoutlets" : 0,
					"bgcolor" : [ 0.858824, 0.858824, 0.858824, 1.0 ],
					"border" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"id" : "obj-33",
					"patching_rect" : [ 435.0, 450.0, 123.0, 70.0 ],
					"numinlets" : 1,
					"numoutlets" : 0,
					"bgcolor" : [ 0.858824, 0.858824, 0.858824, 1.0 ],
					"border" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"id" : "obj-85",
					"patching_rect" : [ 69.0, 338.0, 291.0, 38.0 ],
					"numinlets" : 1,
					"numoutlets" : 0,
					"bgcolor" : [ 0.858824, 0.858824, 0.858824, 1.0 ],
					"border" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"id" : "obj-89",
					"patching_rect" : [ 600.0, 375.0, 245.0, 212.0 ],
					"numinlets" : 1,
					"numoutlets" : 0,
					"bgcolor" : [ 0.858824, 0.858824, 0.858824, 1.0 ],
					"border" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"varname" : "autohelp_top_panel",
					"id" : "obj-5",
					"patching_rect" : [ 3.0, 3.0, 495.0, 52.0 ],
					"numinlets" : 1,
					"numoutlets" : 0,
					"mode" : 1,
					"grad1" : [ 0.27, 0.35, 0.47, 1.0 ],
					"grad2" : [ 0.85, 0.85, 0.85, 1.0 ],
					"background" : 1
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"source" : [ "obj-11", 1 ],
					"destination" : [ "obj-28", 0 ],
					"hidden" : 0,
					"color" : [ 0.117647, 1.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-11", 2 ],
					"destination" : [ "obj-34", 0 ],
					"hidden" : 0,
					"color" : [ 0.0, 0.0, 1.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-11", 3 ],
					"destination" : [ "obj-30", 0 ],
					"hidden" : 0,
					"color" : [ 0.6, 0.0, 0.65098, 1.0 ],
					"midpoints" : [ 309.5, 369.0, 309.5, 369.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-11", 0 ],
					"destination" : [ "obj-22", 0 ],
					"hidden" : 0,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-4", 0 ],
					"destination" : [ "obj-11", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-29", 0 ],
					"destination" : [ "obj-11", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-21", 0 ],
					"destination" : [ "obj-77", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-84", 0 ],
					"destination" : [ "obj-75", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-79", 1 ],
					"destination" : [ "obj-29", 4 ],
					"hidden" : 0,
					"midpoints" : [ 830.5, 282.0, 804.5, 282.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-79", 0 ],
					"destination" : [ "obj-29", 4 ],
					"hidden" : 0,
					"midpoints" : [ 804.5, 270.0, 804.5, 270.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-37", 0 ],
					"destination" : [ "obj-29", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-6", 0 ],
					"destination" : [ "obj-29", 1 ],
					"hidden" : 0,
					"midpoints" : [ 264.5, 285.0, 264.5, 285.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-6", 1 ],
					"destination" : [ "obj-29", 1 ],
					"hidden" : 0,
					"midpoints" : [ 284.5, 270.0, 264.5, 270.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-100", 0 ],
					"destination" : [ "obj-37", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 0 ],
					"destination" : [ "obj-6", 0 ],
					"hidden" : 0,
					"midpoints" : [ 144.5, 207.0, 264.5, 207.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 0 ],
					"destination" : [ "obj-6", 0 ],
					"hidden" : 0,
					"midpoints" : [ 204.5, 208.0, 264.5, 208.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-7", 0 ],
					"destination" : [ "obj-6", 0 ],
					"hidden" : 0,
					"midpoints" : [ 234.5, 203.0, 264.5, 203.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-9", 0 ],
					"destination" : [ "obj-7", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-47", 1 ],
					"destination" : [ "obj-81", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-23", 0 ],
					"destination" : [ "obj-13", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-23", 0 ],
					"destination" : [ "obj-13", 1 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-29", 0 ],
					"destination" : [ "obj-23", 0 ],
					"hidden" : 0,
					"midpoints" : [ 84.5, 325.0, 459.5, 325.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-71", 0 ],
					"destination" : [ "obj-14", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-29", 0 ],
					"destination" : [ "obj-12", 0 ],
					"hidden" : 0,
					"midpoints" : [ 84.5, 324.0, 54.0, 324.0, 54.0, 489.0, 84.5, 489.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-70", 0 ],
					"destination" : [ "obj-29", 3 ],
					"hidden" : 0,
					"midpoints" : [ 714.5, 285.0, 624.5, 285.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-75", 0 ],
					"destination" : [ "obj-70", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-109", 4 ],
					"destination" : [ "obj-39", 0 ],
					"hidden" : 0,
					"midpoints" : [ 348.5, 497.0, 84.5, 497.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-109", 3 ],
					"destination" : [ "obj-15", 1 ],
					"hidden" : 0,
					"midpoints" : [ 293.75, 497.0, 362.5, 497.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-109", 2 ],
					"destination" : [ "obj-19", 0 ],
					"hidden" : 0,
					"midpoints" : [ 239.0, 497.0, 84.5, 497.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-109", 1 ],
					"destination" : [ "obj-15", 0 ],
					"hidden" : 0,
					"midpoints" : [ 184.25, 497.0, 81.5, 497.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-109", 0 ],
					"destination" : [ "obj-18", 0 ],
					"hidden" : 0,
					"midpoints" : [ 129.5, 497.0, 84.5, 497.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-30", 1 ],
					"destination" : [ "obj-109", 3 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 1 ],
					"destination" : [ "obj-109", 2 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-28", 1 ],
					"destination" : [ "obj-109", 1 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-22", 1 ],
					"destination" : [ "obj-109", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-77", 0 ],
					"destination" : [ "obj-71", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-24", 0 ],
					"destination" : [ "obj-29", 2 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-81", 0 ],
					"destination" : [ "obj-24", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
 ]
	}

}
