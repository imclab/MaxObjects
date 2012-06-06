{
	"patcher" : 	{
		"fileversion" : 1,
		"rect" : [ 108.0, 44.0, 1234.0, 632.0 ],
		"bglocked" : 0,
		"defrect" : [ 108.0, 44.0, 1234.0, 632.0 ],
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
					"maxclass" : "newobj",
					"text" : "loadmess 440",
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 1,
					"patching_rect" : [ 705.0, 119.0, 83.0, 20.0 ],
					"hidden" : 1,
					"outlettype" : [ "" ],
					"fontname" : "Arial",
					"id" : "obj-84"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Set frequency",
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"patching_rect" : [ 699.0, 112.0, 83.0, 20.0 ],
					"fontname" : "Arial",
					"id" : "obj-80"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 2,
					"patching_rect" : [ 705.0, 150.0, 58.0, 20.0 ],
					"outlettype" : [ "float", "bang" ],
					"fontname" : "Arial",
					"id" : "obj-75"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "cycle~ 440",
					"numinlets" : 2,
					"fontsize" : 11.595187,
					"numoutlets" : 1,
					"patching_rect" : [ 705.0, 180.0, 66.0, 20.0 ],
					"outlettype" : [ "signal" ],
					"fontname" : "Arial",
					"id" : "obj-70"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Set the window type :",
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"patching_rect" : [ 259.0, 282.0, 124.0, 20.0 ],
					"fontname" : "Arial",
					"id" : "obj-82"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "umenu",
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"types" : [  ],
					"numoutlets" : 3,
					"patching_rect" : [ 270.0, 300.0, 100.0, 20.0 ],
					"items" : [ "Square", ",", "Hanning", ",", "Hamming", ",", "Turkey", ",", "Cosinus", ",", "Lancsoz", ",", "Triangular", ",", "Gaussian", ",", "Bartlett-Hann", ",", "Blackman", ",", "Kaizer", ",", "Nuttall", ",", "Blackman-Harris", ",", "Blackman-Nuttall", ",", "Flat-Top", ",", "Poison" ],
					"outlettype" : [ "int", "", "" ],
					"fontname" : "Arial",
					"id" : "obj-77"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p send",
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"patching_rect" : [ 270.0, 360.0, 45.0, 20.0 ],
					"fontname" : "Arial",
					"id" : "obj-73",
					"patcher" : 					{
						"fileversion" : 1,
						"rect" : [ 29.0, 67.0, 640.0, 480.0 ],
						"bglocked" : 0,
						"defrect" : [ 29.0, 67.0, 640.0, 480.0 ],
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
									"text" : "s spectrum",
									"numinlets" : 1,
									"fontsize" : 11.595187,
									"numoutlets" : 0,
									"patching_rect" : [ 65.0, 166.0, 67.0, 20.0 ],
									"fontname" : "Arial",
									"id" : "obj-54"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numinlets" : 0,
									"numoutlets" : 1,
									"patching_rect" : [ 52.5, 40.0, 25.0, 25.0 ],
									"outlettype" : [ "" ],
									"id" : "obj-59",
									"comment" : ""
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-59", 0 ],
									"destination" : [ "obj-54", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"globalpatchername" : "",
						"fontface" : 0,
						"fontsize" : 12.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"fontname" : "Arial",
						"default_fontsize" : 12.0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "window $1",
					"numinlets" : 2,
					"fontsize" : 11.595187,
					"numoutlets" : 1,
					"patching_rect" : [ 270.0, 330.0, 65.0, 18.0 ],
					"outlettype" : [ "" ],
					"fontname" : "Arial",
					"id" : "obj-71"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "arg 3 : Window type (default : 1 or Hanning)",
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"patching_rect" : [ 525.0, 285.0, 242.0, 20.0 ],
					"fontname" : "Arial",
					"id" : "obj-67"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p send",
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"patching_rect" : [ 1140.0, 420.0, 45.0, 20.0 ],
					"fontname" : "Arial",
					"id" : "obj-61",
					"patcher" : 					{
						"fileversion" : 1,
						"rect" : [ 175.0, 62.0, 640.0, 480.0 ],
						"bglocked" : 0,
						"defrect" : [ 175.0, 62.0, 640.0, 480.0 ],
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
									"text" : "s spectrum",
									"numinlets" : 1,
									"fontsize" : 11.595187,
									"numoutlets" : 0,
									"patching_rect" : [ 65.0, 166.0, 67.0, 20.0 ],
									"fontname" : "Arial",
									"id" : "obj-54"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numinlets" : 0,
									"numoutlets" : 1,
									"patching_rect" : [ 52.5, 40.0, 25.0, 25.0 ],
									"outlettype" : [ "" ],
									"id" : "obj-59",
									"comment" : ""
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-59", 0 ],
									"destination" : [ "obj-54", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"globalpatchername" : "",
						"fontface" : 0,
						"fontsize" : 12.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"fontname" : "Arial",
						"default_fontsize" : 12.0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "loadmess 5",
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 1,
					"patching_rect" : [ 1140.0, 307.0, 70.0, 20.0 ],
					"hidden" : 1,
					"outlettype" : [ "" ],
					"fontname" : "Arial",
					"id" : "obj-16"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "number",
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"minimum" : 1,
					"numoutlets" : 2,
					"patching_rect" : [ 1140.0, 330.0, 50.0, 20.0 ],
					"outlettype" : [ "int", "bang" ],
					"fontname" : "Arial",
					"id" : "obj-26"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "smooth $1",
					"numinlets" : 2,
					"fontsize" : 11.595187,
					"numoutlets" : 1,
					"patching_rect" : [ 1140.0, 390.0, 65.0, 18.0 ],
					"outlettype" : [ "" ],
					"fontname" : "Arial",
					"id" : "obj-56"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Pierre Guillot\nUniversite Paris 8",
					"linecount" : 2,
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"patching_rect" : [ 510.0, 15.0, 150.0, 33.0 ],
					"fontname" : "Arial",
					"id" : "obj-59"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "loadmess 10",
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 1,
					"patching_rect" : [ 1050.0, 307.0, 76.0, 20.0 ],
					"hidden" : 1,
					"outlettype" : [ "" ],
					"fontname" : "Arial",
					"id" : "obj-65"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Polling interval (ms) and smooth value : @interval & @smooth",
					"linecount" : 3,
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"patching_rect" : [ 1050.0, 285.0, 160.0, 46.0 ],
					"fontname" : "Arial",
					"id" : "obj-63"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "number",
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"minimum" : 5,
					"numoutlets" : 2,
					"patching_rect" : [ 1050.0, 330.0, 50.0, 20.0 ],
					"maximum" : 5000,
					"outlettype" : [ "int", "bang" ],
					"fontname" : "Arial",
					"id" : "obj-60"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p send",
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"patching_rect" : [ 1050.0, 420.0, 45.0, 20.0 ],
					"fontname" : "Arial",
					"id" : "obj-53",
					"patcher" : 					{
						"fileversion" : 1,
						"rect" : [ 175.0, 62.0, 640.0, 480.0 ],
						"bglocked" : 0,
						"defrect" : [ 175.0, 62.0, 640.0, 480.0 ],
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
									"text" : "s spectroscope",
									"numinlets" : 1,
									"fontsize" : 11.595187,
									"numoutlets" : 0,
									"patching_rect" : [ 50.0, 181.0, 88.0, 20.0 ],
									"fontname" : "Arial",
									"id" : "obj-55"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "s spectrum",
									"numinlets" : 1,
									"fontsize" : 11.595187,
									"numoutlets" : 0,
									"patching_rect" : [ 65.0, 166.0, 67.0, 20.0 ],
									"fontname" : "Arial",
									"id" : "obj-54"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numinlets" : 0,
									"numoutlets" : 1,
									"patching_rect" : [ 52.5, 40.0, 25.0, 25.0 ],
									"outlettype" : [ "" ],
									"id" : "obj-59",
									"comment" : ""
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-59", 0 ],
									"destination" : [ "obj-55", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-59", 0 ],
									"destination" : [ "obj-54", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"globalpatchername" : "",
						"fontface" : 0,
						"fontsize" : 12.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"fontname" : "Arial",
						"default_fontsize" : 12.0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "interval $1",
					"numinlets" : 2,
					"fontsize" : 11.595187,
					"numoutlets" : 1,
					"patching_rect" : [ 1050.0, 390.0, 64.0, 18.0 ],
					"outlettype" : [ "" ],
					"fontname" : "Arial",
					"id" : "obj-55"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Linear (0) or  logarithmic (1) amplitude scale. Default 1 : @logamp",
					"linecount" : 3,
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"patching_rect" : [ 885.0, 135.0, 161.0, 46.0 ],
					"fontname" : "Arial",
					"id" : "obj-58"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Linear (0) and logarithmic (1) frequency scale. Default 0 : @logfreq",
					"linecount" : 3,
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"patching_rect" : [ 1050.0, 135.0, 163.0, 46.0 ],
					"fontname" : "Arial",
					"id" : "obj-54"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "loadmess 0.",
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 1,
					"patching_rect" : [ 405.0, 236.0, 73.0, 20.0 ],
					"hidden" : 1,
					"outlettype" : [ "" ],
					"fontname" : "Arial",
					"id" : "obj-52"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "loadmess 0",
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 1,
					"patching_rect" : [ 1050.0, 173.0, 70.0, 20.0 ],
					"hidden" : 1,
					"outlettype" : [ "" ],
					"fontname" : "Arial",
					"id" : "obj-51"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "loadmess 1",
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 1,
					"patching_rect" : [ 885.0, 172.0, 70.0, 20.0 ],
					"hidden" : 1,
					"outlettype" : [ "" ],
					"fontname" : "Arial",
					"id" : "obj-50"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p send",
					"numinlets" : 2,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"patching_rect" : [ 1050.0, 255.0, 45.0, 20.0 ],
					"fontname" : "Arial",
					"id" : "obj-34",
					"patcher" : 					{
						"fileversion" : 1,
						"rect" : [ 175.0, 62.0, 640.0, 480.0 ],
						"bglocked" : 0,
						"defrect" : [ 175.0, 62.0, 640.0, 480.0 ],
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
									"text" : "p slider",
									"numinlets" : 1,
									"fontsize" : 11.595187,
									"numoutlets" : 1,
									"patching_rect" : [ 141.0, 100.0, 48.0, 20.0 ],
									"outlettype" : [ "" ],
									"fontname" : "Arial",
									"id" : "obj-71",
									"patcher" : 									{
										"fileversion" : 1,
										"rect" : [ 207.0, 141.0, 640.0, 480.0 ],
										"bglocked" : 0,
										"defrect" : [ 207.0, 141.0, 640.0, 480.0 ],
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
													"maxclass" : "message",
													"text" : "range -70. 0.",
													"numinlets" : 2,
													"fontsize" : 11.595187,
													"numoutlets" : 1,
													"patching_rect" : [ 50.0, 130.0, 76.0, 18.0 ],
													"outlettype" : [ "" ],
													"fontname" : "Arial",
													"id" : "obj-64"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "range 0. 1.",
													"numinlets" : 2,
													"fontsize" : 11.595187,
													"numoutlets" : 1,
													"patching_rect" : [ 125.0, 130.0, 66.0, 18.0 ],
													"outlettype" : [ "" ],
													"fontname" : "Arial",
													"id" : "obj-63"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "select 1",
													"numinlets" : 2,
													"fontsize" : 11.595187,
													"numoutlets" : 2,
													"patching_rect" : [ 95.0, 100.0, 50.0, 20.0 ],
													"outlettype" : [ "bang", "" ],
													"fontname" : "Arial",
													"id" : "obj-62"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"numinlets" : 0,
													"numoutlets" : 1,
													"patching_rect" : [ 95.0, 40.0, 25.0, 25.0 ],
													"outlettype" : [ "int" ],
													"id" : "obj-59",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 82.0, 208.0, 25.0, 25.0 ],
													"id" : "obj-60",
													"comment" : ""
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-63", 0 ],
													"destination" : [ "obj-60", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-64", 0 ],
													"destination" : [ "obj-60", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-59", 0 ],
													"destination" : [ "obj-62", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-62", 1 ],
													"destination" : [ "obj-63", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-62", 0 ],
													"destination" : [ "obj-64", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}
,
									"saved_object_attributes" : 									{
										"globalpatchername" : "",
										"fontface" : 0,
										"fontsize" : 12.0,
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"fontname" : "Arial",
										"default_fontsize" : 12.0
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "s multislider",
									"numinlets" : 1,
									"fontsize" : 11.595187,
									"numoutlets" : 0,
									"patching_rect" : [ 143.0, 161.0, 72.0, 20.0 ],
									"fontname" : "Arial",
									"id" : "obj-61"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "s spectroscope",
									"numinlets" : 1,
									"fontsize" : 11.595187,
									"numoutlets" : 0,
									"patching_rect" : [ 50.0, 181.0, 88.0, 20.0 ],
									"fontname" : "Arial",
									"id" : "obj-55"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "s spectrum",
									"numinlets" : 1,
									"fontsize" : 11.595187,
									"numoutlets" : 0,
									"patching_rect" : [ 65.0, 166.0, 67.0, 20.0 ],
									"fontname" : "Arial",
									"id" : "obj-54"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numinlets" : 0,
									"numoutlets" : 1,
									"patching_rect" : [ 52.5, 40.0, 25.0, 25.0 ],
									"outlettype" : [ "" ],
									"id" : "obj-59",
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numinlets" : 0,
									"numoutlets" : 1,
									"patching_rect" : [ 141.0, 40.0, 25.0, 25.0 ],
									"outlettype" : [ "int" ],
									"id" : "obj-60",
									"comment" : ""
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-60", 0 ],
									"destination" : [ "obj-71", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-59", 0 ],
									"destination" : [ "obj-54", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-59", 0 ],
									"destination" : [ "obj-55", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"globalpatchername" : "",
						"fontface" : 0,
						"fontsize" : 12.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"fontname" : "Arial",
						"default_fontsize" : 12.0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "toggle",
					"numinlets" : 1,
					"numoutlets" : 1,
					"patching_rect" : [ 1050.0, 195.0, 20.0, 20.0 ],
					"outlettype" : [ "int" ],
					"id" : "obj-44"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "logfreq $1",
					"numinlets" : 2,
					"fontsize" : 11.595187,
					"numoutlets" : 1,
					"patching_rect" : [ 1050.0, 225.0, 62.0, 18.0 ],
					"outlettype" : [ "" ],
					"fontname" : "Arial",
					"id" : "obj-45"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "loadmess 0",
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 1,
					"patching_rect" : [ 885.0, 306.0, 70.0, 20.0 ],
					"hidden" : 1,
					"outlettype" : [ "" ],
					"fontname" : "Arial",
					"id" : "obj-48"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Linear",
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"patching_rect" : [ 393.0, 458.0, 45.0, 20.0 ],
					"fontname" : "Arial",
					"id" : "obj-39"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Logarithmic",
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"patching_rect" : [ 30.0, 457.0, 74.0, 20.0 ],
					"fontname" : "Arial",
					"id" : "obj-35"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "0",
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"patching_rect" : [ 391.0, 562.0, 38.0, 20.0 ],
					"fontname" : "Arial",
					"id" : "obj-32"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "1",
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"patching_rect" : [ 394.0, 478.0, 38.0, 20.0 ],
					"fontname" : "Arial",
					"id" : "obj-25"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "loadmess 22050",
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 1,
					"patching_rect" : [ 945.0, 306.0, 96.0, 20.0 ],
					"hidden" : 1,
					"outlettype" : [ "" ],
					"fontname" : "Arial",
					"id" : "obj-18"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p send",
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"patching_rect" : [ 885.0, 420.0, 45.0, 20.0 ],
					"fontname" : "Arial",
					"id" : "obj-114",
					"patcher" : 					{
						"fileversion" : 1,
						"rect" : [ 29.0, 67.0, 640.0, 480.0 ],
						"bglocked" : 0,
						"defrect" : [ 29.0, 67.0, 640.0, 480.0 ],
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
									"text" : "s spectroscope",
									"numinlets" : 1,
									"fontsize" : 11.595187,
									"numoutlets" : 0,
									"patching_rect" : [ 50.0, 181.0, 88.0, 20.0 ],
									"fontname" : "Arial",
									"id" : "obj-55"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "s spectrum",
									"numinlets" : 1,
									"fontsize" : 11.595187,
									"numoutlets" : 0,
									"patching_rect" : [ 65.0, 166.0, 67.0, 20.0 ],
									"fontname" : "Arial",
									"id" : "obj-54"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numinlets" : 0,
									"numoutlets" : 1,
									"patching_rect" : [ 52.5, 40.0, 25.0, 25.0 ],
									"outlettype" : [ "" ],
									"id" : "obj-59",
									"comment" : ""
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-59", 0 ],
									"destination" : [ "obj-54", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-59", 0 ],
									"destination" : [ "obj-55", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"globalpatchername" : "",
						"fontface" : 0,
						"fontsize" : 12.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"fontname" : "Arial",
						"default_fontsize" : 12.0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "pak 0. 0.",
					"numinlets" : 2,
					"fontsize" : 11.595187,
					"numoutlets" : 1,
					"patching_rect" : [ 885.0, 360.0, 55.0, 20.0 ],
					"outlettype" : [ "" ],
					"fontname" : "Arial",
					"id" : "obj-112"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "number",
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"minimum" : 0,
					"numoutlets" : 2,
					"patching_rect" : [ 945.0, 330.0, 50.0, 20.0 ],
					"maximum" : 22050,
					"outlettype" : [ "int", "bang" ],
					"fontname" : "Arial",
					"id" : "obj-111"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "number",
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"minimum" : 0,
					"numoutlets" : 2,
					"patching_rect" : [ 885.0, 330.0, 50.0, 20.0 ],
					"maximum" : 22050,
					"outlettype" : [ "int", "bang" ],
					"fontname" : "Arial",
					"id" : "obj-109"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "domain $1 $2",
					"numinlets" : 2,
					"fontsize" : 11.595187,
					"numoutlets" : 1,
					"patching_rect" : [ 885.0, 390.0, 81.0, 18.0 ],
					"outlettype" : [ "" ],
					"fontname" : "Arial",
					"id" : "obj-107"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Frequency domain values (minimum and maximum in Hz) : @domain",
					"linecount" : 3,
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"patching_rect" : [ 885.0, 285.0, 180.0, 46.0 ],
					"fontname" : "Arial",
					"id" : "obj-106"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"numinlets" : 1,
					"fontsize" : 12.0,
					"minimum" : 0.0,
					"numoutlets" : 2,
					"patching_rect" : [ 405.0, 258.0, 50.0, 20.0 ],
					"maximum" : 1.0,
					"outlettype" : [ "float", "bang" ],
					"fontname" : "Arial",
					"id" : "obj-101"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "pack 0. 100",
					"numinlets" : 2,
					"fontsize" : 12.0,
					"numoutlets" : 1,
					"patching_rect" : [ 405.0, 285.0, 71.0, 20.0 ],
					"outlettype" : [ "" ],
					"fontname" : "Arial",
					"id" : "obj-102"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "line~",
					"numinlets" : 2,
					"fontsize" : 12.0,
					"numoutlets" : 2,
					"patching_rect" : [ 405.0, 315.0, 36.0, 20.0 ],
					"outlettype" : [ "signal", "bang" ],
					"fontname" : "Arial",
					"id" : "obj-103"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "*~",
					"numinlets" : 2,
					"fontsize" : 12.0,
					"numoutlets" : 1,
					"patching_rect" : [ 390.0, 345.0, 33.5, 20.0 ],
					"outlettype" : [ "signal" ],
					"fontname" : "Arial",
					"id" : "obj-104"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "ezadc~",
					"numinlets" : 1,
					"numoutlets" : 2,
					"patching_rect" : [ 810.0, 150.0, 45.0, 45.0 ],
					"outlettype" : [ "signal", "signal" ],
					"id" : "obj-79"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "pg.spectrum~ works quite like the spectroscope.\n",
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"patching_rect" : [ 885.0, 105.0, 267.0, 20.0 ],
					"fontname" : "Arial",
					"id" : "obj-64"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p send",
					"numinlets" : 2,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"patching_rect" : [ 885.0, 255.0, 45.0, 20.0 ],
					"fontname" : "Arial",
					"id" : "obj-62",
					"patcher" : 					{
						"fileversion" : 1,
						"rect" : [ 175.0, 62.0, 640.0, 480.0 ],
						"bglocked" : 0,
						"defrect" : [ 175.0, 62.0, 640.0, 480.0 ],
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
									"text" : "p slider",
									"numinlets" : 1,
									"fontsize" : 11.595187,
									"numoutlets" : 1,
									"patching_rect" : [ 141.0, 100.0, 48.0, 20.0 ],
									"outlettype" : [ "" ],
									"fontname" : "Arial",
									"id" : "obj-71",
									"patcher" : 									{
										"fileversion" : 1,
										"rect" : [ 207.0, 141.0, 640.0, 480.0 ],
										"bglocked" : 0,
										"defrect" : [ 207.0, 141.0, 640.0, 480.0 ],
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
													"maxclass" : "message",
													"text" : "range -70. 0.",
													"numinlets" : 2,
													"fontsize" : 11.595187,
													"numoutlets" : 1,
													"patching_rect" : [ 50.0, 130.0, 76.0, 18.0 ],
													"outlettype" : [ "" ],
													"fontname" : "Arial",
													"id" : "obj-64"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "message",
													"text" : "range 0. 1.",
													"numinlets" : 2,
													"fontsize" : 11.595187,
													"numoutlets" : 1,
													"patching_rect" : [ 125.0, 130.0, 66.0, 18.0 ],
													"outlettype" : [ "" ],
													"fontname" : "Arial",
													"id" : "obj-63"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "newobj",
													"text" : "select 1",
													"numinlets" : 2,
													"fontsize" : 11.595187,
													"numoutlets" : 2,
													"patching_rect" : [ 95.0, 100.0, 50.0, 20.0 ],
													"outlettype" : [ "bang", "" ],
													"fontname" : "Arial",
													"id" : "obj-62"
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "inlet",
													"numinlets" : 0,
													"numoutlets" : 1,
													"patching_rect" : [ 95.0, 40.0, 25.0, 25.0 ],
													"outlettype" : [ "int" ],
													"id" : "obj-59",
													"comment" : ""
												}

											}
, 											{
												"box" : 												{
													"maxclass" : "outlet",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 82.0, 208.0, 25.0, 25.0 ],
													"id" : "obj-60",
													"comment" : ""
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"source" : [ "obj-62", 0 ],
													"destination" : [ "obj-64", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-62", 1 ],
													"destination" : [ "obj-63", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-59", 0 ],
													"destination" : [ "obj-62", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-64", 0 ],
													"destination" : [ "obj-60", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
, 											{
												"patchline" : 												{
													"source" : [ "obj-63", 0 ],
													"destination" : [ "obj-60", 0 ],
													"hidden" : 0,
													"midpoints" : [  ]
												}

											}
 ]
									}
,
									"saved_object_attributes" : 									{
										"globalpatchername" : "",
										"fontface" : 0,
										"fontsize" : 12.0,
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"fontname" : "Arial",
										"default_fontsize" : 12.0
									}

								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "s multislider",
									"numinlets" : 1,
									"fontsize" : 11.595187,
									"numoutlets" : 0,
									"patching_rect" : [ 143.0, 161.0, 72.0, 20.0 ],
									"fontname" : "Arial",
									"id" : "obj-61"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "s spectroscope",
									"numinlets" : 1,
									"fontsize" : 11.595187,
									"numoutlets" : 0,
									"patching_rect" : [ 50.0, 181.0, 88.0, 20.0 ],
									"fontname" : "Arial",
									"id" : "obj-55"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "s spectrum",
									"numinlets" : 1,
									"fontsize" : 11.595187,
									"numoutlets" : 0,
									"patching_rect" : [ 65.0, 166.0, 67.0, 20.0 ],
									"fontname" : "Arial",
									"id" : "obj-54"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numinlets" : 0,
									"numoutlets" : 1,
									"patching_rect" : [ 52.5, 40.0, 25.0, 25.0 ],
									"outlettype" : [ "" ],
									"id" : "obj-59",
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numinlets" : 0,
									"numoutlets" : 1,
									"patching_rect" : [ 141.0, 40.0, 25.0, 25.0 ],
									"outlettype" : [ "int" ],
									"id" : "obj-60",
									"comment" : ""
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-71", 0 ],
									"destination" : [ "obj-61", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-59", 0 ],
									"destination" : [ "obj-55", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-59", 0 ],
									"destination" : [ "obj-54", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-60", 0 ],
									"destination" : [ "obj-71", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"globalpatchername" : "",
						"fontface" : 0,
						"fontsize" : 12.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"fontname" : "Arial",
						"default_fontsize" : 12.0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "r multislider",
					"numinlets" : 0,
					"fontsize" : 11.595187,
					"numoutlets" : 1,
					"patching_rect" : [ 270.0, 420.0, 70.0, 20.0 ],
					"outlettype" : [ "" ],
					"fontname" : "Arial",
					"id" : "obj-66"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "r spectroscope",
					"numinlets" : 0,
					"fontsize" : 11.595187,
					"numoutlets" : 1,
					"patching_rect" : [ 180.0, 420.0, 87.0, 20.0 ],
					"outlettype" : [ "" ],
					"fontname" : "Arial",
					"id" : "obj-57"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "toggle",
					"numinlets" : 1,
					"numoutlets" : 1,
					"patching_rect" : [ 885.0, 195.0, 20.0, 20.0 ],
					"outlettype" : [ "int" ],
					"id" : "obj-27"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "logamp $1",
					"numinlets" : 2,
					"fontsize" : 11.595187,
					"numoutlets" : 1,
					"patching_rect" : [ 885.0, 225.0, 65.0, 18.0 ],
					"outlettype" : [ "" ],
					"fontname" : "Arial",
					"id" : "obj-30"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "-126dB",
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"patching_rect" : [ 36.0, 562.0, 48.0, 20.0 ],
					"fontname" : "Arial",
					"id" : "obj-49"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "0dB",
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"patching_rect" : [ 39.0, 476.0, 38.0, 20.0 ],
					"fontname" : "Arial",
					"id" : "obj-46"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s results",
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"patching_rect" : [ 30.0, 390.0, 54.0, 20.0 ],
					"fontname" : "Arial",
					"id" : "obj-22"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s spectrum",
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"patching_rect" : [ 1140.0, 555.0, 67.0, 20.0 ],
					"fontname" : "Arial",
					"id" : "obj-24"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "toggle",
					"numinlets" : 1,
					"numoutlets" : 1,
					"patching_rect" : [ 1140.0, 495.0, 20.0, 20.0 ],
					"outlettype" : [ "int" ],
					"id" : "obj-23"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "resize $1",
					"numinlets" : 2,
					"fontsize" : 11.595187,
					"numoutlets" : 1,
					"patching_rect" : [ 1140.0, 525.0, 58.0, 18.0 ],
					"outlettype" : [ "" ],
					"fontname" : "Arial",
					"id" : "obj-21"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "r spectrum",
					"numinlets" : 0,
					"fontsize" : 11.595187,
					"numoutlets" : 1,
					"patching_rect" : [ 135.0, 300.0, 65.0, 20.0 ],
					"outlettype" : [ "" ],
					"fontname" : "Arial",
					"id" : "obj-15"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Be careful : A lot of Max/Msp objects don't take lists with over 256 elements, in this case the resize attribute, resizes the list for a maximum of 256 elements.",
					"linecount" : 4,
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"patching_rect" : [ 885.0, 495.0, 256.0, 60.0 ],
					"fontname" : "Arial",
					"id" : "obj-19"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 870.0, 480.0, 346.0, 113.0 ],
					"border" : 2,
					"bgcolor" : [ 0.858824, 0.858824, 0.858824, 1.0 ],
					"id" : "obj-4"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "loadmess 2",
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 1,
					"patching_rect" : [ 30.0, 150.0, 70.0, 20.0 ],
					"hidden" : 1,
					"outlettype" : [ "" ],
					"fontname" : "Arial",
					"id" : "obj-100"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Overlapping is useful with high window sizes to make up the analyse time.\n\nHop size = window size / overlapping",
					"linecount" : 5,
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"patching_rect" : [ 525.0, 450.0, 205.0, 73.0 ],
					"fontname" : "Arial",
					"id" : "obj-95"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "For better performances set a low window size and for better results set a high window size.",
					"linecount" : 3,
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"patching_rect" : [ 525.0, 405.0, 169.0, 46.0 ],
					"fontname" : "Arial",
					"id" : "obj-94"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "For:\nsampling rate = 44100 Hz\nwindows size = 1024 samples\nfrequency band = 43 Hz",
					"linecount" : 4,
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"patching_rect" : [ 525.0, 345.0, 169.0, 60.0 ],
					"fontname" : "Arial",
					"id" : "obj-93"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Frequency band  :\nsampling rate / windows size (in Hz)",
					"linecount" : 2,
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"patching_rect" : [ 525.0, 315.0, 193.0, 33.0 ],
					"fontname" : "Arial",
					"id" : "obj-91"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "arg 2 : FFT overlapping (default : 2)",
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"patching_rect" : [ 525.0, 270.0, 210.0, 20.0 ],
					"fontname" : "Arial",
					"id" : "obj-88"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "arg 1 : FFT window size (default : 1024)",
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"patching_rect" : [ 525.0, 255.0, 217.0, 20.0 ],
					"fontname" : "Arial",
					"id" : "obj-87"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Turn audio on",
					"linecount" : 3,
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"patching_rect" : [ 439.0, 392.0, 42.0, 46.0 ],
					"fontname" : "Arial",
					"id" : "obj-43"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Select the source",
					"linecount" : 2,
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"patching_rect" : [ 30.0, 135.0, 88.0, 33.0 ],
					"fontname" : "Arial",
					"id" : "obj-42"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Play with noise",
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"patching_rect" : [ 480.0, 105.0, 138.0, 20.0 ],
					"fontname" : "Arial",
					"id" : "obj-41"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Select an audio file",
					"linecount" : 2,
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"patching_rect" : [ 265.0, 99.0, 62.0, 33.0 ],
					"fontname" : "Arial",
					"id" : "obj-40"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "umenu",
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"types" : [  ],
					"numoutlets" : 3,
					"patching_rect" : [ 30.0, 180.0, 88.0, 20.0 ],
					"items" : [ "None", ",", "Audio", "file", ",", "Noise", ",", "Cycle~", ",", "Adc~" ],
					"outlettype" : [ "int", "", "" ],
					"fontname" : "Arial",
					"id" : "obj-37"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "selector~ 4",
					"numinlets" : 5,
					"fontsize" : 11.595187,
					"numoutlets" : 1,
					"patching_rect" : [ 90.0, 240.0, 258.0, 20.0 ],
					"outlettype" : [ "signal" ],
					"fontname" : "Arial",
					"id" : "obj-29"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "umenu",
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"types" : [  ],
					"numoutlets" : 3,
					"patching_rect" : [ 390.0, 105.0, 88.0, 20.0 ],
					"items" : [ "display", ",", "lowpass", ",", "highpass", ",", "bandpass", ",", "bandstop", ",", "peaknotch", ",", "lowshelf", ",", "highshelf", ",", "resonant", ",", "allpass" ],
					"outlettype" : [ "int", "", "" ],
					"fontname" : "Arial",
					"id" : "obj-47"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "noise~",
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 1,
					"patching_rect" : [ 210.0, 180.0, 43.0, 20.0 ],
					"outlettype" : [ "signal" ],
					"fontname" : "Arial",
					"id" : "obj-68"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "biquad~",
					"numinlets" : 6,
					"fontsize" : 11.595187,
					"numoutlets" : 1,
					"patching_rect" : [ 210.0, 210.0, 79.0, 20.0 ],
					"outlettype" : [ "signal" ],
					"fontname" : "Arial",
					"id" : "obj-69"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "filtergraph~",
					"numinlets" : 8,
					"autoout" : 1,
					"fontsize" : 8.998901,
					"domain" : [ 0.0, 22050.0 ],
					"numoutlets" : 7,
					"patching_rect" : [ 390.0, 135.0, 279.0, 77.0 ],
					"outlettype" : [ "list", "float", "float", "float", "float", "list", "int" ],
					"hcurvecolor" : [ 1.0, 0.086275, 0.086275, 1.0 ],
					"bwidthcolor" : [ 0.462745, 0.47451, 0.65098, 1.0 ],
					"hbwidthcolor" : [ 0.823529, 0.290196, 0.211765, 1.0 ],
					"bgcolor" : [ 0.913725, 0.913725, 1.0, 1.0 ],
					"id" : "obj-81",
					"fgcolor" : [ 0.756863, 0.756863, 1.0, 1.0 ],
					"markercolor" : [ 0.509804, 0.509804, 0.509804, 1.0 ],
					"logfreq" : 0,
					"nfilters" : 1,
					"setfilter" : [ 0, 8, 0, 0, 0, 7112.90332, 1.0, 1.714286, 0.0001, 22050.0, 0.0001, 16.0, 0.5, 25.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "multislider",
					"size" : 512,
					"numinlets" : 1,
					"numoutlets" : 2,
					"patching_rect" : [ 90.0, 480.0, 300.0, 100.0 ],
					"setminmax" : [ -70.0, 0.0 ],
					"outlettype" : [ "", "" ],
					"thickness" : 5,
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"id" : "obj-14"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "spectroscope~",
					"numinlets" : 2,
					"range" : [ 0.0, 1.0 ],
					"numoutlets" : 1,
					"patching_rect" : [ 90.0, 480.0, 300.0, 100.0 ],
					"curvecolor" : [ 0.145098, 0.07451, 0.376471, 1.0 ],
					"outlettype" : [ "" ],
					"id" : "obj-12",
					"fgcolor" : [ 0.239216, 0.643137, 0.709804, 1.0 ],
					"interval" : 10
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "ezdac~",
					"numinlets" : 2,
					"numoutlets" : 0,
					"patching_rect" : [ 394.0, 392.0, 45.0, 45.0 ],
					"id" : "obj-13"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "pg.spectrum~ 1024 1 1",
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 1,
					"patching_rect" : [ 90.0, 345.0, 129.0, 20.0 ],
					"outlettype" : [ "list" ],
					"fontname" : "Arial",
					"id" : "obj-11",
					"saved_object_attributes" : 					{
						"domain" : [ 0.0, 22050.0 ],
						"window" : 1,
						"resize" : 0,
						"smooth" : 5,
						"logamp" : 1,
						"logfreq" : 0,
						"interval" : 10
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "toggle",
					"numinlets" : 1,
					"numoutlets" : 1,
					"patching_rect" : [ 240.0, 105.0, 20.0, 20.0 ],
					"outlettype" : [ "int" ],
					"id" : "obj-9"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "toggle",
					"numinlets" : 1,
					"numoutlets" : 1,
					"patching_rect" : [ 210.0, 105.0, 20.0, 20.0 ],
					"outlettype" : [ "int" ],
					"id" : "obj-8"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "loop $1",
					"numinlets" : 2,
					"fontsize" : 12.0,
					"numoutlets" : 1,
					"patching_rect" : [ 240.0, 135.0, 50.0, 18.0 ],
					"outlettype" : [ "" ],
					"fontname" : "Arial",
					"id" : "obj-7"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "sfplay~ 2",
					"numinlets" : 2,
					"fontsize" : 12.0,
					"numoutlets" : 3,
					"patching_rect" : [ 150.0, 165.0, 59.0, 20.0 ],
					"outlettype" : [ "signal", "signal", "bang" ],
					"fontname" : "Arial",
					"id" : "obj-6",
					"save" : [ "#N", "sfplay~", "", 2, 120960, 0, "", ";" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "open",
					"numinlets" : 2,
					"fontsize" : 12.0,
					"numoutlets" : 1,
					"patching_rect" : [ 150.0, 105.0, 37.0, 18.0 ],
					"outlettype" : [ "" ],
					"fontname" : "Arial",
					"id" : "obj-10"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"varname" : "autohelp_top_title",
					"text" : "pg.spectrum~",
					"numinlets" : 1,
					"fontface" : 3,
					"fontsize" : 20.871338,
					"numoutlets" : 0,
					"patching_rect" : [ 10.0, 7.0, 485.0, 30.0 ],
					"textcolor" : [ 0.93, 0.93, 0.97, 1.0 ],
					"frgb" : [ 0.93, 0.93, 0.97, 1.0 ],
					"fontname" : "Arial",
					"id" : "obj-1"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"varname" : "autohelp_top_digest",
					"text" : "Signal spectrogram",
					"numinlets" : 1,
					"fontsize" : 12.754705,
					"numoutlets" : 0,
					"patching_rect" : [ 10.0, 36.0, 483.0, 21.0 ],
					"textcolor" : [ 0.93, 0.93, 0.97, 1.0 ],
					"frgb" : [ 0.93, 0.93, 0.97, 1.0 ],
					"fontname" : "Arial",
					"id" : "obj-2"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"varname" : "autohelp_top_description",
					"text" : "pg.spectrum~ performs a FFT and displays the spectrum.",
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"patching_rect" : [ 8.0, 57.0, 415.0, 20.0 ],
					"fontname" : "Arial",
					"id" : "obj-3"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 30.0, 450.0, 435.0, 144.0 ],
					"border" : 2,
					"bgcolor" : [ 0.858824, 0.858824, 0.858824, 1.0 ],
					"id" : "obj-17"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 375.0, 90.0, 318.0, 132.0 ],
					"border" : 2,
					"bgcolor" : [ 0.858824, 0.858824, 0.858824, 1.0 ],
					"id" : "obj-31"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 379.0, 377.0, 106.0, 70.0 ],
					"border" : 2,
					"bgcolor" : [ 0.858824, 0.858824, 0.858824, 1.0 ],
					"id" : "obj-33"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 135.0, 90.0, 210.0, 74.0 ],
					"border" : 2,
					"bgcolor" : [ 0.858824, 0.858824, 0.858824, 1.0 ],
					"id" : "obj-36"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 15.0, 135.0, 111.0, 80.0 ],
					"border" : 2,
					"bgcolor" : [ 0.858824, 0.858824, 0.858824, 1.0 ],
					"id" : "obj-38"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 84.0, 339.0, 169.0, 33.0 ],
					"border" : 2,
					"bgcolor" : [ 0.858824, 0.858824, 0.858824, 1.0 ],
					"id" : "obj-85"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 510.0, 240.0, 276.0, 299.0 ],
					"border" : 2,
					"bgcolor" : [ 0.858824, 0.858824, 0.858824, 1.0 ],
					"id" : "obj-89"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 870.0, 90.0, 344.0, 381.0 ],
					"border" : 2,
					"bgcolor" : [ 0.858824, 0.858824, 0.858824, 1.0 ],
					"id" : "obj-72"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 255.0, 270.0, 122.0, 125.0 ],
					"border" : 2,
					"bgcolor" : [ 0.858824, 0.858824, 0.858824, 1.0 ],
					"id" : "obj-78"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 696.0, 94.0, 86.0, 124.0 ],
					"border" : 2,
					"bgcolor" : [ 0.858824, 0.858824, 0.858824, 1.0 ],
					"id" : "obj-74"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 788.0, 94.0, 80.0, 123.0 ],
					"border" : 2,
					"bgcolor" : [ 0.858824, 0.858824, 0.858824, 1.0 ],
					"id" : "obj-83"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"varname" : "autohelp_top_panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 5.0, 5.0, 495.0, 52.0 ],
					"grad1" : [ 0.27, 0.35, 0.47, 1.0 ],
					"grad2" : [ 0.85, 0.85, 0.85, 1.0 ],
					"mode" : 1,
					"id" : "obj-5",
					"background" : 1
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"source" : [ "obj-11", 0 ],
					"destination" : [ "obj-14", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-15", 0 ],
					"destination" : [ "obj-11", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-11", 0 ],
					"destination" : [ "obj-22", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-29", 0 ],
					"destination" : [ "obj-11", 0 ],
					"hidden" : 0,
					"midpoints" : [ 99.5, 318.0, 99.5, 318.0 ]
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
					"source" : [ "obj-52", 0 ],
					"destination" : [ "obj-101", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-79", 1 ],
					"destination" : [ "obj-29", 4 ],
					"hidden" : 0,
					"midpoints" : [ 845.5, 225.0, 792.0, 225.0, 792.0, 225.0, 423.0, 225.0, 423.0, 225.0, 357.0, 225.0, 357.0, 225.0, 338.5, 225.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-79", 0 ],
					"destination" : [ "obj-29", 4 ],
					"hidden" : 0,
					"midpoints" : [ 819.5, 195.0, 818.0, 195.0, 818.0, 225.0, 423.0, 225.0, 423.0, 225.0, 357.0, 225.0, 357.0, 225.0, 338.5, 225.0 ]
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
					"source" : [ "obj-29", 0 ],
					"destination" : [ "obj-12", 0 ],
					"hidden" : 0,
					"midpoints" : [ 99.5, 318.0, 16.0, 318.0, 16.0, 417.0, 99.5, 417.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-69", 0 ],
					"destination" : [ "obj-29", 2 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-6", 0 ],
					"destination" : [ "obj-29", 1 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-6", 1 ],
					"destination" : [ "obj-29", 1 ],
					"hidden" : 0,
					"midpoints" : [ 179.5, 225.0, 159.25, 225.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-65", 0 ],
					"destination" : [ "obj-60", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-60", 0 ],
					"destination" : [ "obj-55", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-55", 0 ],
					"destination" : [ "obj-53", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-51", 0 ],
					"destination" : [ "obj-44", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-50", 0 ],
					"destination" : [ "obj-27", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-44", 0 ],
					"destination" : [ "obj-45", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-44", 0 ],
					"destination" : [ "obj-34", 1 ],
					"hidden" : 0,
					"midpoints" : [ 1059.5, 220.0, 1115.0, 220.0, 1115.0, 247.0, 1085.5, 247.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-45", 0 ],
					"destination" : [ "obj-34", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-107", 0 ],
					"destination" : [ "obj-114", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-111", 0 ],
					"destination" : [ "obj-112", 1 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-112", 0 ],
					"destination" : [ "obj-107", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-109", 0 ],
					"destination" : [ "obj-112", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-101", 0 ],
					"destination" : [ "obj-102", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-102", 0 ],
					"destination" : [ "obj-103", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-30", 0 ],
					"destination" : [ "obj-62", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 0 ],
					"destination" : [ "obj-62", 1 ],
					"hidden" : 0,
					"midpoints" : [ 894.5, 222.0, 951.0, 222.0, 951.0, 249.0, 920.5, 249.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-57", 0 ],
					"destination" : [ "obj-12", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-66", 0 ],
					"destination" : [ "obj-14", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 0 ],
					"destination" : [ "obj-30", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-21", 0 ],
					"destination" : [ "obj-24", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-23", 0 ],
					"destination" : [ "obj-21", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
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
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 0 ],
					"destination" : [ "obj-6", 0 ],
					"hidden" : 0,
					"midpoints" : [ 219.5, 142.0, 159.5, 142.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-7", 0 ],
					"destination" : [ "obj-6", 0 ],
					"hidden" : 0,
					"midpoints" : [ 249.5, 158.0, 159.5, 158.0 ]
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
					"source" : [ "obj-68", 0 ],
					"destination" : [ "obj-69", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-81", 0 ],
					"destination" : [ "obj-69", 1 ],
					"hidden" : 0,
					"midpoints" : [ 399.5, 228.0, 345.0, 228.0, 345.0, 201.0, 231.5, 201.0 ]
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
					"source" : [ "obj-18", 0 ],
					"destination" : [ "obj-111", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-48", 0 ],
					"destination" : [ "obj-109", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-26", 0 ],
					"destination" : [ "obj-56", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 0 ],
					"destination" : [ "obj-26", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-56", 0 ],
					"destination" : [ "obj-61", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-71", 0 ],
					"destination" : [ "obj-73", 0 ],
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
					"source" : [ "obj-70", 0 ],
					"destination" : [ "obj-29", 3 ],
					"hidden" : 0,
					"midpoints" : [ 714.5, 225.0, 291.0, 225.0, 291.0, 237.0, 278.75, 237.0 ]
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
					"source" : [ "obj-103", 0 ],
					"destination" : [ "obj-104", 1 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-104", 0 ],
					"destination" : [ "obj-13", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-104", 0 ],
					"destination" : [ "obj-13", 1 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-29", 0 ],
					"destination" : [ "obj-104", 0 ],
					"hidden" : 0,
					"midpoints" : [ 99.5, 266.0, 399.0, 266.0, 399.0, 336.0, 399.5, 336.0 ]
				}

			}
 ]
	}

}
