<?php

function get_lotto_keno_autopicks_numbers_efficiency_form_t($form, &$form_state){
    
    drupal_add_css(drupal_get_path('module', 'lotto_core') . '/css/number_grid.css', array('group' => CSS_DEFAULT, 'type' => 'file'));
    
    $form = array();
    if (isset($draw_num)){
	$last_keno_draw_num = $draw_num;
    } else $last_keno_draw_num = get_last_keno_drawnumber("lotto_keno") - 1;
    $last_keno_draw_num_val = $last_keno_draw_num + 1;
    $top_of = 10;
    $defaults = array('enable_numbers_grid'=>1, 'enable_performance_grid'=>1, 'enable_betting_system_grid'=>1);
    
    $numbers_spiral = get_lotto_autopicks_apd_numbers_quick("lotto_keno", $last_keno_draw_num, $last_keno_draw_num_val);
       
    $form['efficiency']=array(
	'#type'=>  'fieldset',
	'#title'=>t("Autopicks Numbers Efficiency:"),
	'#collapsible'=>true,
	'#collapsed'=>false,
	'#prefix'=>'<div id="ajx_autopicks_efficiency_wrapper" >',
	'#suffix'=>'</div>'
    );
    
    $form['efficiency']['draw_number_prev']=array(
	'#type'=>'button',
	'#value'=>t('Prev'),
	'#ajax'=>array(
	    'callback' => 'ajx_numbers_draw_number_prev_t',
	    'wrapper'=>'ajx_autopicks_efficiency_wrapper',
	    'method'=>'replace'
	),
	'#prefix'=>'<div class="container-inline">',
    );	

    
    $form['efficiency']['draw_number']=array(
	'#type'=>  'textfield',
	'#title'=>t("Draw#: "),
	'#default_value'=> $last_keno_draw_num,
	'#size'=> 11	
    );
    
    $form['efficiency']['draw_number_next']=array(
	'#type'=>'button',
	'#value'=>t('Next'),
	'#ajax'=>array(
	    'callback' => 'ajx_numbers_draw_number_next_t',
	    'wrapper'=>'ajx_autopicks_efficiency_wrapper',
	    'method'=>'replace'
	),
    );
    $form['efficiency']['autopicks_profile'] = array(
	'#type'=>'select',
	'#title'=>'Profile:',
	'#options'=>array(
	    0=>'Select Profile',
	    1=>'DiagWinNormal',
	    2=>'DiagWinNormal-t',
	    3=>'DiagWinSpiral',
	    4=>'DiagWinSpiral-t'
	),
	'#default_value'=>4
    );
    
    
    $form['efficiency']['refresh']=array(
	'#type'=>'button',
	'#value'=>t('Refresh'),
	'#ajax'=>array(
	    'callback' => 'ajx_autopicks_efficiency_refresh',
	    'wrapper'=>'ajx_autopicks_efficiency_wrapper',
	    'method'=>'replace'
	),
    );
     
    $form['efficiency']['top_of']=array(
	'#type'=>  'textfield',
	'#title'=>t("No of Picks#: "),
	'#default_value'=>15,
	'#size'=> 11	
    );
    
    $form['efficiency']['draw_number_val']=array(
	'#type'=>  'textfield',
	'#title'=>t("Draw Result#: "),
	'#default_value'=>$last_keno_draw_num_val,
	'#size'=> 11	
    );
    
    $form['efficiency']['enable_numbers_grid']=array(
	'#type'=>  'checkbox',
	'#title'=>t("Numbers Grid: "),
	'#default_value'=>$defaults['enable_numbers_grid']
    );
    
    $form['efficiency']['enable_performance_grid']=array(
	'#type'=>  'checkbox',
	'#title'=>t("Performance Grid: "),
	'#default_value'=>$defaults['enable_performance_grid']
    );
     
    $form['efficiency']['enable_betting_system_grid']=array(
	'#type'=>  'checkbox',
	'#title'=>t("Betting System Grid: "),
	'#default_value'=>$defaults['enable_betting_system_grid']
    );
     
    $form['efficiency']['numbers']=array(
	'#type'=>  'fieldset',
	'#title'=>t("Numbers Grid:"),
	'#collapsible'=>true,
	'#collapsed'=>false,	
	'#prefix'=>'<div id="ajx_autopicks_efficiency_numbers_wrapper" >',
	'#suffix'=>'</div>'
    );
    
    $form['efficiency']['numbers']['grid']=array(
	'#markup'=>lotto_keno_autopicks_pillar_diagwin_numbers_grid_create_spiral_t("lotto_keno", $numbers_spiral)
	
    );
    
     $form['efficiency']['numbers_performance']=array(
	'#type'=>  'fieldset',
	'#title'=>t("Numbers Performance:"),
	'#collapsible'=>true,
	'#collapsed'=>false,	
	'#prefix'=>'<div id="ajx_autopicks_efficiency_numbers_performance_wrapper" >',
	'#suffix'=>'</div>'
    );
    
    
    $form['efficiency']['numbers_performance']['grid']=array(
	'#markup'=>lotto_keno_autopicks_numbers_performance_grid_create_t("lotto_keno", $numbers_spiral),
	
    );
    
    $form['efficiency']['betting_system']=array(
	'#type'=>  'fieldset',
	'#title'=>t("Betting System:"),
	'#collapsible'=>true,
	'#collapsed'=>false,	
	'#prefix'=>'<div id="ajx_autopicks_efficiency_betting_system_wrapper" >',
	'#suffix'=>'</div>'
    );
    
    $form['efficiency']['betting_system']['profile']=array(
	'#type'=>  'select',
	'#title'=>t("Betting Profile: "),
	'#default_value'=> 1,
	'#options'=>array(
	    0=>t("Select Profile"),
	    1=>t("Exclude Current Results(~20)"),
	    2=>t("Exclude Current-Last Results(~35)")
	),	
    );
    
    $form['efficiency']['betting_system']['each_set_of']=array(
	'#type'=>  'select',
	'#title'=>t("Each Set of: "),
	'#default_value'=> 10,
	'#options'=>array(
	    0=>t("Select Profile"),
	    1=>t("1s"),
	    2=>t("2s"),
	    3=>t("3s"),
	    4=>t("4s"),
	    5=>t("5s"),
	    6=>t("6s"),
	    7=>t("7s"),
	    8=>t("8s"),
	    9=>t("9s"),
	    10=>t("10s")
	),
	'#prefix'=>'&nbsp &nbsp'
    );
    $form['efficiency']['betting_system']['number_of_bets']=array(
	'#type'=>  'textfield',
	'#title'=>t("Bets#: "),
	'#default_value'=> 8,
	'#size'=>3,
	'#prefix'=>'&nbsp &nbsp'
    );
    
    $form['efficiency']['betting_system']['grid']=array(
	'#markup'=>lotto_keno_betting_system_performance_grid_create("lotto_keno", $numbers_spiral, 2, 7, 0)	
    );
    
    return $form;
}

function ajx_numbers_draw_number_prev_t($form, $form_state){
    $draw_num = $form_state['values']['draw_number'];
    $draw_num_val = $form_state['values']['draw_number_val'];
    $draw_num_prev = $draw_num-1;
    $draw_num_prev_val = $draw_num_val - 1;
    $top_of = $form_state['values']['top_of'];
    $enable_numbers_grid = $form_state['values']['enable_numbers_grid'];
    $enable_performance_grid = $form_state['values']['enable_performance_grid'];
    
    $numbers_spiral = get_lotto_autopicks_apd_numbers_quick("lotto_keno", $draw_num_prev, $draw_num_prev_val );
     if($enable_numbers_grid == 1){
	$numbers_grid = lotto_keno_autopicks_pillar_diagwin_numbers_grid_create_spiral_t("lotto_keno", $numbers_spiral);
     } else $numbers_grid = '';
     if($enable_performance_grid == 1){
	$numbers_performance_grid = lotto_keno_autopicks_numbers_performance_grid_create_t("lotto_keno", $numbers_spiral);
     } else $numbers_performance_grid = '';
    //$numbers_score_grid = lotto_keno_autopicks_pillar_diagwin_numbers_score_grid_create_spiral("lotto_keno", $numbers_spiral);
    
    $form['efficiency']['draw_number']['#value'] = $draw_num_prev;
    $form['efficiency']['draw_number_val']['#value'] = $draw_num_prev_val;
    $form['efficiency']['numbers']['grid']['#markup'] = $numbers_grid;
    $form['efficiency']['numbers_performance']['grid']['#markup'] = $numbers_performance_grid;
    //$form['efficiency']['numbers_score']['grid']['#markup'] = $numbers_score_grid;
    
	
    return $form['efficiency'];
}

function ajx_numbers_draw_number_next_t($form, $form_state){
    $draw_num = $form_state['values']['draw_number'];
    $draw_num_val = $form_state['values']['draw_number_val'];
    $draw_num_next = $draw_num + 1;
    $draw_num_next_val = $draw_num_val + 1;
    $top_of = $form_state['values']['top_of'];
    $enable_numbers_grid = $form_state['values']['enable_numbers_grid'];
    $enable_performance_grid = $form_state['values']['enable_performance_grid'];
    
    $numbers_spiral = get_lotto_autopicks_apd_numbers_quick("lotto_keno", $draw_num_next, $draw_num_next_val);
    if($enable_numbers_grid == 1){
	$numbers_grid = lotto_keno_autopicks_pillar_diagwin_numbers_grid_create_spiral_t("lotto_keno", $numbers_spiral);
    } else $numbers_grid = '';
    if($enable_performance_grid == 1){
	$numbers_performance_grid = lotto_keno_autopicks_numbers_performance_grid_create_t("lotto_keno", $numbers_spiral);
    } else $numbers_performance_grid = '';
    //$numbers_score_grid = lotto_keno_autopicks_pillar_diagwin_numbers_score_grid_create_spiral("lotto_keno", $numbers_spiral);
    
    
    $form['efficiency']['enable_numbers_grid']['#value'] = $enable_numbers_grid;
    $form['efficiency']['enable_performance_grid']['#value'] = $enable_performance_grid;
    $form['efficiency']['draw_number']['#value'] = $draw_num_next;
    $form['efficiency']['draw_number_val']['#value'] = $draw_num_next_val;
    $form['efficiency']['numbers']['grid']['#markup'] = $numbers_grid;
    $form['efficiency']['numbers_performance']['grid']['#markup'] = $numbers_performance_grid;
    //$form['efficiency']['numbers_score']['grid']['#markup'] = $numbers_score_grid; 
    
    return $form['efficiency'];
}

function lotto_keno_autopicks_pillar_diagwin_numbers_grid_create_spiral_t($lottery_name, $apd_numbers){
    $number_grid='';
    switch($lottery_name){
	case 'lotto_max':
	    break;
	case 'lotto_keno':
	    $column_max = 27;
	    $row_max = 80;
	    
	    $draw_details = $apd_numbers['draw_details'];
	    $lotto_results = $apd_numbers['lotto_results'];
	    $autopicks_diagonal = $apd_numbers['autopick_nbrs']['diagonal'];
	    $autopicks_ladder = $apd_numbers['autopick_nbrs']['ladder'];
	    $diagwin5 = $apd_numbers['diagwin5'];
	    $diagwin10 = $apd_numbers['diagwin10'];
	    $diagwin20 = $apd_numbers['diagwin20'];
	    $diagwin50 = $apd_numbers['diagwin50'];
	    $diagwin100 = $apd_numbers['diagwin100'];
	    $ratios_sum = get_lotto_autopicks_apd_numbers_ratio_sum($lottery_name, $apd_numbers);
	    
	    $header = "<table class=	\"number_grid\" ><tbody>";
	    
	    $label1 = "<tr><th></th>";
	    $label1 .= "<th colspan=\"2\" >Autopicks</th>";
	    $label1 .= "<th></th>";
	    $label1 .= "<th colspan=\"3\" >Diagwin5</th>";
	    $label1 .= "<th></th>";
	    $label1 .= "<th colspan=\"3\" >Diagwin10</th>";
	    $label1 .= "<th></th>";
	    $label1 .= "<th colspan=\"3\" >Diagwin20</th>";
	    $label1 .= "<th></th>";
	    $label1 .= "<th colspan=\"3\" >Diagwin50</th>";
	    $label1 .= "<th></th>";
	    $label1 .= "<th colspan=\"3\" >Diagwin100</th>";
	    $label1 .= "<th></th>";
	    $label1 .= "<th colspan=\"4\" >RatioSum</th>";
	    $label1 .= "</tr>";
	    
	    $label2 = "<tr><th></th>";
	    $label2 .= "<th>Diagonal</th>";
	    $label2 .= "<th>Ladder</th>";
	    $label2 .= "<th></th>";
	    $label2 .= "<th>Pillar</th>";
	    $label2 .= "<th>Stepup</th>";
	    $label2 .= "<th>Stepdown</th>";
	    $label2 .= "<th></th>";
	    $label2 .= "<th>Pillar</th>";
	    $label2 .= "<th>Stepup</th>";
	    $label2 .= "<th>Stepdown</th>";
	    $label2 .= "<th></th>";
	    $label2 .= "<th>Pillar</th>";
	    $label2 .= "<th>Stepup</th>";
	    $label2 .= "<th>Stepdown</th>";
	    $label2 .= "<th></th>";
	    $label2 .= "<th>Pillar</th>";
	    $label2 .= "<th>Stepup</th>";
	    $label2 .= "<th>Stepdown</th>";
	    $label2 .= "<th></th>";
	    $label2 .= "<th>Pillar</th>";
	    $label2 .= "<th>Stepup</th>";
	    $label2 .= "<th>Stepdown</th>";
	    $label2 .= "<th></th>";
	    $label2 .= "<th>Overall</th>";
	    $label2 .= "<th>Pillar</th>";
	    $label2 .= "<th>Stepup</th>";
	    $label2 .= "<th>Stepdown</th>";
	    $label2 .= "</tr>";
	    
	    //predifined table cells
	    $predifined_tds=array();
	    $predifined_tds['result_0']="<td>";
	    $predifined_tds['result_1']="<td class=\"green\" >";
	    
	    
	    $body_data = array();
	    
	    $x=0;$y=0;$z=$row_max;
	    for($y=0; $y <= $column_max; $y++){
		$x=0; //reset $x to 0 at beginning
		
		    if($y == 0){
			for($x=0;$x < $z; $x++){
			    $seq=$x+1;
			    $body_data[$x][$y]="<th>".$seq."</th>";
			} 
		    }elseif ($y == 1){
			foreach($autopicks_diagonal as $ind_ad=>$num_ad){
			    $body_data[$x][$y] = $predifined_tds['result_'.$lotto_results[$num_ad]];
			    $body_data[$x][$y] .= $num_ad."</td>";
			    $x++;
			}
		    } elseif ($y == 2){
			foreach( $autopicks_ladder as $ind_al=>$num_al){
			    $body_data[$x][$y] = $predifined_tds['result_'.$lotto_results[$num_al]];
			    $body_data[$x][$y] .= $num_al."</td>";
			    $x++;
			}
		    } elseif ($y == 4){
			foreach( $diagwin5['pillar'] as $num_5p=>$rat_5p){
			    $body_data[$x][$y] = $predifined_tds['result_'.$lotto_results[$num_5p]];
			    $body_data[$x][$y] .= $num_5p."(".$rat_5p.")</td>";
			    $x++;
			}			
		    } elseif ($y == 5){
			foreach( $diagwin5['stepup'] as $num_5su=>$rat_5su){
			    $body_data[$x][$y] = $predifined_tds['result_'.$lotto_results[$num_5su]];
			    $body_data[$x][$y] .= $num_5su."(".$rat_5su.")</td>";
			    $x++;
			}			
		    } elseif ($y == 6){
			foreach( $diagwin5['stepdown'] as $num_5sd=>$rat_5sd){
			    $body_data[$x][$y] = $predifined_tds['result_'.$lotto_results[$num_5sd]];
			    $body_data[$x][$y] .= $num_5sd."(".$rat_5sd.")</td>";
			    $x++;
			}			
		    } elseif ($y == 8){
			foreach( $diagwin10['pillar'] as $num_5p=>$rat_5p){
			    $body_data[$x][$y] = $predifined_tds['result_'.$lotto_results[$num_5p]];
			    $body_data[$x][$y] .= $num_5p."(".$rat_5p.")</td>";
			    $x++;
			}			
		    } elseif ($y == 9){
			foreach( $diagwin10['stepup'] as $num_5su=>$rat_5su){
			    $body_data[$x][$y] = $predifined_tds['result_'.$lotto_results[$num_5su]];
			    $body_data[$x][$y] .= $num_5su."(".$rat_5su.")</td>";
			    $x++;
			}			
		    } elseif ($y == 10){
			foreach( $diagwin10['stepdown'] as $num_5sd=>$rat_5sd){
			    $body_data[$x][$y] = $predifined_tds['result_'.$lotto_results[$num_5sd]];
			    $body_data[$x][$y] .= $num_5sd."(".$rat_5sd.")</td>";
			    $x++;
			}			
		    } elseif ($y == 12){
			foreach( $diagwin20['pillar'] as $num_5p=>$rat_5p){
			    $body_data[$x][$y] = $predifined_tds['result_'.$lotto_results[$num_5p]];
			    $body_data[$x][$y] .= $num_5p."(".$rat_5p.")</td>";
			    $x++;
			}			
		    } elseif ($y == 13){
			foreach( $diagwin20['stepup'] as $num_5su=>$rat_5su){
			    $body_data[$x][$y] = $predifined_tds['result_'.$lotto_results[$num_5su]];
			    $body_data[$x][$y] .= $num_5su."(".$rat_5su.")</td>";
			    $x++;
			}			
		    } elseif ($y == 14){
			foreach( $diagwin20['stepdown'] as $num_5sd=>$rat_5sd){
			    $body_data[$x][$y] = $predifined_tds['result_'.$lotto_results[$num_5sd]];
			    $body_data[$x][$y] .= $num_5sd."(".$rat_5sd.")</td>";
			    $x++;
			}			
		    } elseif ($y == 16){
			foreach( $diagwin50['pillar'] as $num_5p=>$rat_5p){
			    $body_data[$x][$y] = $predifined_tds['result_'.$lotto_results[$num_5p]];
			    $body_data[$x][$y] .= $num_5p."(".$rat_5p.")</td>";
			    $x++;
			}			
		    } elseif ($y == 17){
			foreach( $diagwin50['stepup'] as $num_5su=>$rat_5su){
			    $body_data[$x][$y] = $predifined_tds['result_'.$lotto_results[$num_5su]];
			    $body_data[$x][$y] .= $num_5su."(".$rat_5su.")</td>";
			    $x++;
			}			
		    } elseif ($y == 18){
			foreach( $diagwin50['stepdown'] as $num_5sd=>$rat_5sd){
			    $body_data[$x][$y] = $predifined_tds['result_'.$lotto_results[$num_5sd]];
			    $body_data[$x][$y] .= $num_5sd."(".$rat_5sd.")</td>";
			    $x++;
			}			
		    } elseif ($y == 20){
			foreach( $diagwin100['pillar'] as $num_5p=>$rat_5p){
			    $body_data[$x][$y] = $predifined_tds['result_'.$lotto_results[$num_5p]];
			    $body_data[$x][$y] .= $num_5p."(".$rat_5p.")</td>";
			    $x++;
			}			
		    } elseif ($y == 21){
			foreach( $diagwin100['stepup'] as $num_5su=>$rat_5su){
			    $body_data[$x][$y] = $predifined_tds['result_'.$lotto_results[$num_5su]];
			    $body_data[$x][$y] .= $num_5su."(".$rat_5su.")</td>";
			    $x++;
			}			
		    } elseif ($y == 22){
			foreach( $diagwin100['stepdown'] as $num_5sd=>$rat_5sd){
			    $body_data[$x][$y] = $predifined_tds['result_'.$lotto_results[$num_5sd]];
			    $body_data[$x][$y] .= $num_5sd."(".$rat_5sd.")</td>";
			    $x++;
			}			
		    } elseif ($y == 24){
			foreach( $ratios_sum['overall'] as $num_sumo=>$rat_sumo){
			    $body_data[$x][$y] = $predifined_tds['result_'.$lotto_results[$num_sumo]];
			    $body_data[$x][$y] .= $num_sumo."(".$rat_sumo.")</td>";
			    $x++;
			}
		    } elseif ($y == 25){
			foreach( $ratios_sum['pillar'] as $num_sump=>$rat_sump){
			    $body_data[$x][$y] = $predifined_tds['result_'.$lotto_results[$num_sump]];
			    $body_data[$x][$y] .= $num_sump."(".$rat_sump.")</td>";
			    $x++;
			}
		    } elseif ($y == 26){
			foreach( $ratios_sum['stepup'] as $num_sumsu=>$rat_sumsu){
			    $body_data[$x][$y] = $predifined_tds['result_'.$lotto_results[$num_sumsu]];
			    $body_data[$x][$y] .= $num_sumsu."(".$rat_sumsu.")</td>";
			    $x++;
			}
		    } elseif ($y == 27){
			foreach( $ratios_sum['stepdown'] as $num_sumsd=>$rat_sumsd){
			    $body_data[$x][$y] = $predifined_tds['result_'.$lotto_results[$num_sumsd]];
			    $body_data[$x][$y] .= $num_sumsd."(".$rat_sumsd.")</td>";
			    $x++;
			}
		    } else {
			    for($x=0; $x<$z; $x++){
			    $body_data[$x][$y] = "<th></th>";
			    }
		    }
		    
		    //fille in with blank cells.
		    while($x < $z){
			$body_data[$x][$y] = "<td class=\"black\" ></td>";		
			$x++;
		    }
	    }
	    
	   
	    
	    $body="";
	    foreach($body_data as $x=>$data){
		$body .= "<tr>";
		foreach($data as $y=>$num){
		    $body .= $num;
		}
		$body .= "</tr>";
	    }
	    
	    $footer= "</tbody></table>";

	    $number_grid .= $header . $label1 . $label2 .$body .$footer;
	    
	break;
    }    
    
    return $number_grid;
}

function lotto_keno_autopicks_numbers_performance_grid_create_t($lottery_name, $apd_numbers, $range=array(5, 10)){
    $number_performance_grid='';
    switch($lottery_name){
	case 'lotto_max':
	    break;
	case 'lotto_keno':
	    $range_limit = $range[0];
	    $range_group = $range[1];
	    
	    $lotto_results = $apd_numbers['lotto_results'];
	    $autopicks_diagonal = $apd_numbers['autopick_nbrs']['diagonal'];
	    $autopicks_ladder = $apd_numbers['autopick_nbrs']['ladder'];
	    $diagwin5 = $apd_numbers['diagwin5'];
	    $diagwin10 = $apd_numbers['diagwin10'];
	    $diagwin20 = $apd_numbers['diagwin20'];
	    $diagwin50 = $apd_numbers['diagwin50'];
	    $diagwin100 = $apd_numbers['diagwin100'];    
	    $ratios_sum = get_lotto_autopicks_apd_numbers_ratio_sum($lottery_name, $apd_numbers);
	    
	    $header = "<table class=\"number_performance_grid\" ><tbody>";
	    
	     $label1 = "<tr><th></th>";
	    $label1 .= "<th colspan=\"4\" >Autopicks</th>";
	    $label1 .= "<th></th>";
	    $label1 .= "<th colspan=\"6\" >Diagwin5</th>";
	    $label1 .= "<th></th>";
	    $label1 .= "<th colspan=\"6\" >Diagwin10</th>";
	    $label1 .= "<th></th>";
	    $label1 .= "<th colspan=\"6\" >Diagwin20</th>";
	    $label1 .= "<th></th>";
	    $label1 .= "<th colspan=\"6\" >Diagwin50</th>";
	    $label1 .= "<th></th>";
	    $label1 .= "<th colspan=\"6\" >Diagwin100</th>";
	    $label1 .= "<th></th>";
	    $label1 .= "<th colspan=\"8\" >RatioSum</th>";
	    $label1 .= "</tr>";
	    
	    $label2 = "<tr><th></th>";
	    $label2 .= "<th colspan=\"2\" >Diagonal</th>";
	    $label2 .= "<th colspan=\"2\" >Ladder</th>";
	    $label2 .= "<th></th>";
	    $label2 .= "<th colspan=\"2\" >Pillar</th>";
	    $label2 .= "<th colspan=\"2\" >Stepup</th>";
	    $label2 .= "<th colspan=\"2\" >Stepdown</th>";
	    $label2 .= "<th></th>";
	    $label2 .= "<th colspan=\"2\" >Pillar</th>";
	    $label2 .= "<th colspan=\"2\" >Stepup</th>";
	    $label2 .= "<th colspan=\"2\" >Stepdown</th>";
	    $label2 .= "<th></th>";
	    $label2 .= "<th colspan=\"2\" >Pillar</th>";
	    $label2 .= "<th colspan=\"2\" >Stepup</th>";
	    $label2 .= "<th colspan=\"2\" >Stepdown</th>";
	    $label2 .= "<th></th>";
	    $label2 .= "<th colspan=\"2\" >Pillar</th>";
	    $label2 .= "<th colspan=\"2\" >Stepup</th>";
	    $label2 .= "<th colspan=\"2\" >Stepdown</th>";
	    $label2 .= "<th></th>";
	    $label2 .= "<th colspan=\"2\" >Pillar</th>";
	    $label2 .= "<th colspan=\"2\" >Stepup</th>";
	    $label2 .= "<th colspan=\"2\" >Stepdown</th>";
	    $label2 .= "<th></th>";
	    $label2 .= "<th colspan=\"2\" >Overall</th>";
	    $label2 .= "<th colspan=\"2\" >Pillar</th>";
	    $label2 .= "<th colspan=\"2\" >Stepup</th>";
	    $label2 .= "<th colspan=\"2\" >Stepdown</th>";
	    $label2 .= "</tr>";
	    	      
	    $nbr_performance = array();
	    
	    $x=0; $rslt=array();
	    foreach( $autopicks_diagonal as $num_ad ){
		array_push($rslt, $lotto_results[$num_ad]);
		$x++;
		if(($x % $range_limit) == 0){
		    $div = (int)($x / $range_limit);
		    $nbr_performance['autopicks']['diagonal'][$div] = $rslt;
		    $rslt = array();
		}
	    }
	    while(((int)($x / $range_limit)) < 16){
		$x++;
		if(($x % $range_limit) == 0){
		    $div = ((int)($x / $range_limit));
		    $nbr_performance['autopicks']['diagonal'][$div] = $rslt;
		    $rslt = array();
		}
	    }
	    
	    $x=0; $rslt=array();
	    foreach( $autopicks_ladder as $num_al ){
		array_push($rslt, $lotto_results[$num_al]);
		$x++;
		if(($x % $range_limit) == 0){
		    $div = (int)($x / $range_limit);
		    $nbr_performance['autopicks']['ladder'][$div] = $rslt;
		    $rslt = array();
		}
	    }
	    while(((int)($x / $range_limit)) < 16){
		$x++;
		if(($x % $range_limit) == 0){
		    $div = ((int)($x / $range_limit));
		    $nbr_performance['autopicks']['ladder'][$div] = $rslt;
		    $rslt = array();
		}
	    }
	    
	    $rslt=array();
	    foreach( $diagwin5 as $cat_5=>$data_5 ){
		 $x=0; 
		foreach($data_5 as $num_5=>$rat_5){
		    array_push($rslt, $lotto_results[$num_5]);
		    $x++;
		    if(($x % $range_limit) == 0){
			$div = (int)($x / $range_limit);
			$nbr_performance['diagwin5'][$cat_5][$div] = $rslt;
			$rslt = array();
		    }
		}
	    }
	    
	    $rslt=array();
	    foreach( $diagwin10 as $cat_10=>$data_10 ){
		 $x=0; 
		foreach($data_10 as $num_10=>$rat_10){
		    array_push($rslt, $lotto_results[$num_10]);
		    $x++;
		    if(($x % $range_limit) == 0){
			$div = (int)($x / $range_limit);
			$nbr_performance['diagwin10'][$cat_10][$div] = $rslt;
			$rslt = array();
		    }
		}
	    }
	    
	   $rslt=array();
	    foreach( $diagwin20 as $cat_20=>$data_20 ){
		 $x=0; 
		foreach($data_20 as $num_20=>$rat_20){
		    array_push($rslt, $lotto_results[$num_20]);
		    $x++;
		    if(($x % $range_limit) == 0){
			$div = (int)($x / $range_limit);
			$nbr_performance['diagwin20'][$cat_20][$div] = $rslt;
			$rslt = array();
		    }
		}
	    }
	    
	   $rslt=array();
	    foreach( $diagwin50 as $cat_50=>$data_50 ){
		 $x=0; 
		foreach($data_50 as $num_50=>$rat_50){
		    array_push($rslt, $lotto_results[$num_50]);
		    $x++;
		    if(($x % $range_limit) == 0){
			$div = (int)($x / $range_limit);
			$nbr_performance['diagwin50'][$cat_50][$div] = $rslt;
			$rslt = array();
		    }
		}
	    }
	    
	    $rslt=array();
	    foreach( $diagwin100 as $cat_100=>$data_100 ){
		$x=0;
		foreach($data_100 as $num_100=>$rat_100){
		    array_push($rslt, $lotto_results[$num_100]);
		    $x++;
		    if(($x % $range_limit) == 0){
			$div = (int)($x / $range_limit);
			$nbr_performance['diagwin100'][$cat_100][$div] = $rslt;
			$rslt = array();
		    }
		}
	    }
	    $rslt=array();
	    foreach( $ratios_sum as $cat_rsum=>$data_rsum ){
		$x=0;
		foreach($data_rsum as $num_rsum=>$rat_rsum){
		    array_push($rslt, $lotto_results[$num_rsum]);
		    $x++;
		    if(($x % $range_limit) == 0){
			$div = (int)($x / $range_limit);
			$nbr_performance['ratio_sum'][$cat_rsum][$div] = $rslt;
			$rslt = array();
		    }
		}
	    }
	    
	    
	    
	    $body = "";
	    $y=0;
	    for($x=1; $x <= 16; $x++ ){
		$body .= "<tr>";
		$body .= "<th>".($x * $range_limit)."</th>";
		$body .= "<td>".  array_sum($nbr_performance['autopicks']['diagonal'][$x])."</td>";
		$body .= ($y == 0) ? "<td rowspan=\"2\" >".(array_sum($nbr_performance['autopicks']['diagonal'][$x]) + array_sum($nbr_performance['autopicks']['diagonal'][($x + 1)]))."</td>":"";    
		$body .= "<td>".  array_sum($nbr_performance['autopicks']['ladder'][$x])."</td>";
		$body .= ($y == 0) ? "<td rowspan=\"2\" >".(array_sum($nbr_performance['autopicks']['ladder'][$x]) + array_sum($nbr_performance['autopicks']['ladder'][($x + 1)]))."</td>":"";  
		$body .= "<th></th>";
		
		$body .= "<td>".  array_sum($nbr_performance['diagwin5']['pillar'][$x])."</td>";
		$body .= ($y == 0) ? "<td rowspan=\"2\" >".(array_sum($nbr_performance['diagwin5']['pillar'][$x]) + array_sum($nbr_performance['diagwin5']['pillar'][($x + 1)]))."</td>":"";  
		$body .= "<td>".  array_sum($nbr_performance['diagwin5']['stepup'][$x])."</td>";
		$body .= ($y == 0) ? "<td rowspan=\"2\" >".(array_sum($nbr_performance['diagwin5']['stepup'][$x]) + array_sum($nbr_performance['diagwin5']['stepup'][($x + 1)]))."</td>":"";  
		$body .= "<td>".  array_sum($nbr_performance['diagwin5']['stepdown'][$x])."</td>";
		$body .= ($y == 0) ? "<td rowspan=\"2\" >".(array_sum($nbr_performance['diagwin5']['stepdown'][$x]) + array_sum($nbr_performance['diagwin5']['stepdown'][($x + 1)]))."</td>":"";  
		$body .= "<th></th>";
		
		$body .= "<td>".  array_sum($nbr_performance['diagwin10']['pillar'][$x])."</td>";
		$body .= ($y == 0) ? "<td rowspan=\"2\" >".(array_sum($nbr_performance['diagwin10']['pillar'][$x]) + array_sum($nbr_performance['diagwin10']['pillar'][($x + 1)]))."</td>":"";  
		$body .= "<td>".  array_sum($nbr_performance['diagwin10']['stepup'][$x])."</td>";
		$body .= ($y == 0) ? "<td rowspan=\"2\" >".(array_sum($nbr_performance['diagwin10']['stepup'][$x]) + array_sum($nbr_performance['diagwin10']['stepup'][($x + 1)]))."</td>":"";  
		$body .= "<td>".  array_sum($nbr_performance['diagwin10']['stepdown'][$x])."</td>";
		$body .= ($y == 0) ? "<td rowspan=\"2\" >".(array_sum($nbr_performance['diagwin10']['stepdown'][$x]) + array_sum($nbr_performance['diagwin10']['stepdown'][($x + 1)]))."</td>":"";  
		$body .= "<th></th>";
		
		$body .= "<td>".  array_sum($nbr_performance['diagwin20']['pillar'][$x])."</td>";
		$body .= ($y == 0) ? "<td rowspan=\"2\" >".(array_sum($nbr_performance['diagwin20']['pillar'][$x]) + array_sum($nbr_performance['diagwin20']['pillar'][($x + 1)]))."</td>":"";  
		$body .= "<td>".  array_sum($nbr_performance['diagwin20']['stepup'][$x])."</td>";
		$body .= ($y == 0) ? "<td rowspan=\"2\" >".(array_sum($nbr_performance['diagwin20']['stepup'][$x]) + array_sum($nbr_performance['diagwin20']['stepup'][($x + 1)]))."</td>":"";  
		$body .= "<td>".  array_sum($nbr_performance['diagwin20']['stepdown'][$x])."</td>";
		$body .= ($y == 0) ? "<td rowspan=\"2\" >".(array_sum($nbr_performance['diagwin20']['stepdown'][$x]) + array_sum($nbr_performance['diagwin20']['stepdown'][($x + 1)]))."</td>":"";  
		$body .= "<th></th>";
		
		$body .= "<td>".  array_sum($nbr_performance['diagwin50']['pillar'][$x])."</td>";
		$body .= ($y == 0) ? "<td rowspan=\"2\" >".(array_sum($nbr_performance['diagwin50']['pillar'][$x]) + array_sum($nbr_performance['diagwin50']['pillar'][($x + 1)]))."</td>":"";  
		$body .= "<td>".  array_sum($nbr_performance['diagwin50']['stepup'][$x])."</td>";
		$body .= ($y == 0) ? "<td rowspan=\"2\" >".(array_sum($nbr_performance['diagwin50']['stepup'][$x]) + array_sum($nbr_performance['diagwin50']['stepup'][($x + 1)]))."</td>":"";  
		$body .= "<td>".  array_sum($nbr_performance['diagwin50']['stepdown'][$x])."</td>";
		$body .= ($y == 0) ? "<td rowspan=\"2\" >".(array_sum($nbr_performance['diagwin50']['stepdown'][$x]) + array_sum($nbr_performance['diagwin50']['stepdown'][($x + 1)]))."</td>":"";  
		$body .= "<th></th>";
		
		$body .= "<td>".  array_sum($nbr_performance['diagwin100']['pillar'][$x])."</td>";
		$body .= ($y == 0) ? "<td rowspan=\"2\" >".(array_sum($nbr_performance['diagwin100']['pillar'][$x]) + array_sum($nbr_performance['diagwin100']['pillar'][($x + 1)]))."</td>":"";  
		$body .= "<td>".  array_sum($nbr_performance['diagwin100']['stepup'][$x])."</td>";
		$body .= ($y == 0) ? "<td rowspan=\"2\" >".(array_sum($nbr_performance['diagwin100']['stepup'][$x]) + array_sum($nbr_performance['diagwin100']['stepup'][($x + 1)]))."</td>":"";  
		$body .= "<td>".  array_sum($nbr_performance['diagwin100']['stepdown'][$x])."</td>";
		$body .= ($y == 0) ? "<td rowspan=\"2\" >".(array_sum($nbr_performance['diagwin100']['stepdown'][$x]) + array_sum($nbr_performance['diagwin100']['stepdown'][($x + 1)]))."</td>":"";  
		$body .= "<th></th>";
		
		$body .= "<td>".  array_sum($nbr_performance['ratio_sum']['overall'][$x])."</td>";
		$body .= ($y == 0) ? "<td rowspan=\"2\" >".(array_sum($nbr_performance['ratio_sum']['overall'][$x]) + array_sum($nbr_performance['ratio_sum']['overall'][($x + 1)]))."</td>":"";  
		$body .= "<td>".  array_sum($nbr_performance['ratio_sum']['pillar'][$x])."</td>";
		$body .= ($y == 0) ? "<td rowspan=\"2\" >".(array_sum($nbr_performance['ratio_sum']['pillar'][$x]) + array_sum($nbr_performance['ratio_sum']['pillar'][($x + 1)]))."</td>":"";  
		$body .= "<td>".  array_sum($nbr_performance['ratio_sum']['stepup'][$x])."</td>";
		$body .= ($y == 0) ? "<td rowspan=\"2\" >".(array_sum($nbr_performance['ratio_sum']['stepup'][$x]) + array_sum($nbr_performance['ratio_sum']['stepup'][($x + 1)]))."</td>":"";  
		$body .= "<td>".  array_sum($nbr_performance['ratio_sum']['stepdown'][$x])."</td>";
		$body .= ($y == 0) ? "<td rowspan=\"2\" >".(array_sum($nbr_performance['ratio_sum']['stepdown'][$x]) + array_sum($nbr_performance['ratio_sum']['stepdown'][($x + 1)]))."</td>":"";  
		
		$body .= "</tr>";
		
		if($y == 0){
		    $y = 1;
		} else $y = 0;
	    }	    	    
	    
	    $footer ="</tbody></table>";
	    
	    $number_performance_grid .= $header . $label1 . $label2 .$body .$footer;
	    break;
    }
    return $number_performance_grid;
}

function get_lotto_autopicks_apd_numbers_ratio_sum($lottery_name, $apd_numbers){
    switch($lottery_name){
	case 'lotto_max':
	    break;
	case 'lotto_keno':
	    $lotto_results = $apd_numbers['lotto_results'];
	    $autopicks_diagonal = $apd_numbers['autopick_nbrs']['diagonal'];
	    $autopicks_ladder = $apd_numbers['autopick_nbrs']['ladder'];
	    $diagwin5 = $apd_numbers['diagwin5'];
	    $diagwin10 = $apd_numbers['diagwin10'];
	    $diagwin20 = $apd_numbers['diagwin20'];
	    $diagwin50 = $apd_numbers['diagwin50'];
	    $diagwin100 = $apd_numbers['diagwin100'];
	    
	    $z=80; $ratios_pillar = array();
	    for($x=1; $x <= $z; $x++){
		$ratios_pillar[$x] = 0.0;
		$ratios_pillar[$x] += $diagwin5['pillar'][$x];
		$ratios_pillar[$x] += $diagwin10['pillar'][$x];
		$ratios_pillar[$x] += $diagwin20['pillar'][$x];
		$ratios_pillar[$x] += $diagwin50['pillar'][$x];
		$ratios_pillar[$x] += $diagwin100['pillar'][$x];
	    }
	    
	    $ratios_stepup = array();
	    for($x=1; $x <= $z; $x++){
		$ratios_stepup[$x] = 0.0;
		$ratios_stepup[$x] += $diagwin5['stepup'][$x];
		$ratios_stepup[$x] += $diagwin10['stepup'][$x];
		$ratios_stepup[$x] += $diagwin20['stepup'][$x];
		$ratios_stepup[$x] += $diagwin50['stepup'][$x];
		$ratios_stepup[$x] += $diagwin100['stepup'][$x];
	    }
	    
	    $ratios_stepdown = array();
	    for($x=1; $x <= $z; $x++){
		$ratios_stepdown[$x] = 0.0;
		$ratios_stepdown[$x] += $diagwin5['stepdown'][$x];
		$ratios_stepdown[$x] += $diagwin10['stepdown'][$x];
		$ratios_stepdown[$x] += $diagwin20['stepdown'][$x];
		$ratios_stepdown[$x] += $diagwin50['stepdown'][$x];
		$ratios_stepdown[$x] += $diagwin100['stepdown'][$x];
	    }
	    
	    $ratios_overall = array();
	    for($x=1; $x <= $z; $x++){
		$ratios_overall[$x] = 0.0;
		$ratios_overall[$x] += $ratios_pillar[$x];
		$ratios_overall[$x] += $ratios_stepdown[$x];
		$ratios_overall[$x] += $ratios_stepdown[$x];
	    }
	    
	    arsort($ratios_overall);
	    arsort($ratios_pillar);
	    arsort($ratios_stepup);
	    arsort($ratios_stepdown);
	    
	    $ratios_sum=array();
	    $ratios_sum['overall'] = $ratios_overall;
	    $ratios_sum['pillar'] = $ratios_pillar;
	    $ratios_sum['stepup'] = $ratios_stepup;
	    $ratios_sum['stepdown'] = $ratios_stepdown;
	    
	    break;
    }
    return $ratios_sum;
}

function lotto_keno_betting_system_bettable_numbers_get($lottery_name, $apd_numbers, $betting_profile=1){
    
    switch($lottery_name){
	case 'lotto_max':
	    break;
	case 'lotto_keno':
	    $draw_num = $apd_numbers['draw_details']['draw_num'];
	    $lotto_results = $apd_numbers['lotto_results'];
	    $diagwin5 = $apd_numbers['diagwin5'];
	    $diagwin10 = $apd_numbers['diagwin10'];
	    $diagwin20 = $apd_numbers['diagwin20'];
	    $diagwin50 = $apd_numbers['diagwin50'];
	    $diagwin100 = $apd_numbers['diagwin100'];
	    
	    switch($betting_profile){
		case 1:
		    $unlucky_numbers = profile_exclude_currently_won_numbers($lottery_name, $draw_num);
		    break;		    
		case 2:
		    $unlucky_numbers = profile_exclude_current_n_last_won_numbers($lottery_name, $draw_num);
		    break;
	    }
	   
	
	$betting_numbers = array();
	foreach($diagwin5 as $cat_5=>$data_5){
	    $betting_numbers['diagwin5'][$cat_5] = array();
		foreach($data_5 as $num_5=>$rat_5){
		    if( !in_array($num_5, $unlucky_numbers))
		    array_push($betting_numbers['diagwin5'][$cat_5], $num_5);
		}
	}
	
	foreach($diagwin10 as $cat_10=>$data_10){
	    $betting_numbers['diagwin10'][$cat_10] = array();
		foreach($data_10 as $num_10=>$rat_10){
		    if( !in_array($num_10, $unlucky_numbers))
		    array_push($betting_numbers['diagwin10'][$cat_10], $num_10);
		}
	}
	
	foreach($diagwin20 as $cat_20=>$data_20){
	    $betting_numbers['diagwin20'][$cat_20] = array();
		foreach($data_20 as $num_20=>$rat_20){
		    if( !in_array($num_20, $unlucky_numbers))
		    array_push($betting_numbers['diagwin20'][$cat_20], $num_20);
		}
	}
	
	foreach($diagwin50 as $cat_50=>$data_50){
	    $betting_numbers['diagwin50'][$cat_50] = array();
		foreach($data_50 as $num_50=>$rat_50){
		    if( !in_array($num_50, $unlucky_numbers))
		    array_push($betting_numbers['diagwin50'][$cat_50], $num_50);
		}
	}
	
	foreach($diagwin100 as $cat_100=>$data_100){
	    $betting_numbers['diagwin100'][$cat_100] = array();
		foreach($data_100 as $num_100=>$rat_100){
		    if( !in_array($num_100, $unlucky_numbers))
		    array_push($betting_numbers['diagwin100'][$cat_100], $num_100);
		}
	}
	
	 break;	 
    }
    
    return $betting_numbers;
}

function lotto_keno_betting_system_bettable_numbers_bet($bettable_numbers, $set_of_each, $number_of_bets=0){
    $bets_sets =array();
    
    foreach($bettable_numbers as $diagwin_cat=>$data_diag){	
	foreach($data_diag as $cat=>$bets){	    
	    $x=0;$y=0;
	    foreach($bets as $ind=>$bet){
		if($x >= $set_of_each ){		    
		    $x=0;
		    $y++;		   
		}
		$bets_sets[$diagwin_cat][$cat][$y][$ind] = $bet;
		$x++;
	    }
	}
    }
    
    return $bets_sets;
}

function lotto_keno_betting_system_bettable_numbers_bets_validate($bettable_numbers_bets, $apd_numbers){
    $validation_outcome = array();
    
    $results = $apd_numbers['lotto_results'];
    $lotto_results = array();
    foreach($results as $num=>$res){
	if ($res == 1){
	    array_push($lotto_results, $num);
	}
    }
    
    foreach($bettable_numbers_bets as $diagwin_cat=>$data_diag){	
	foreach($data_diag as $cat=>$bets){	    	    
	    foreach($bets as $ind=>$sets){
		$matches = array_intersect($sets, $lotto_results);
		$validation_outcome[$diagwin_cat][$cat][$ind] = $matches;
	    }
	}
    }
    return $validation_outcome;
}

function lotto_keno_betting_system_bets_performance_summary_quick($lottery_name, $apd_numbers, $betting_profile=1, $set_of_each=10, $number_of_bets=0){
    $bets_performance_summary=array();
    switch($lottery_name){
	case 'lotto_max':
	    break;
	case 'lotto_keno':
	    $bettable_numbers = lotto_keno_betting_system_bettable_numbers_get($lottery_name, $apd_numbers, $betting_profile);
	    $bettable_numbers_bets = lotto_keno_betting_system_bettable_numbers_bet($bettable_numbers, $set_of_each, $number_of_bets);
	    $validation_outcome = lotto_keno_betting_system_bettable_numbers_bets_validate($bettable_numbers_bets, $apd_numbers);
	    $summary_empty = array(
			  'picks'=>0,
			  'bets'=>0,
			  'matches'=> array(),
			  'win'=>array()			    
			   );
	
	    foreach($validation_outcome as $diagwin_cat=>$data_diag){	
		foreach($data_diag as $cat=>$bets){
		    $bets_performance_summary[$diagwin_cat][$cat] = $summary_empty;
		    $bets_performance_summary[$diagwin_cat][$cat]['picks'] = $set_of_each;
		    $bets_performance_summary[$diagwin_cat][$cat]['bets'] = count($bets);
		    
		    foreach($bets as $ind=>$matches){
			$match_count = count($matches);
			if( !isset($bets_performance_summary[$diagwin_cat][$cat]['matches'][$match_count])){
			    $bets_performance_summary[$diagwin_cat][$cat]['matches'][$match_count] = 0;
			    $bets_performance_summary[$diagwin_cat][$cat]['win'][$match_count] = 0;
			} 
			
			$bets_performance_summary[$diagwin_cat][$cat]['matches'][$match_count] += 1;
			$bets_performance_summary[$diagwin_cat][$cat]['win'][$match_count] += validate_ticket($lottery_name, $set_of_each, $match_count);
		    }
		}
	    }
	    break;
    }
   return $bets_performance_summary;
}
function lotto_keno_betting_system_performance_grid_create($lottery_name, $apd_numbers, $betting_profile=1, $set_of_each=10, $number_of_bets=0){
    $betting_system_performance_grid='';
    switch($lottery_name){
	case 'lotto_max':
	    break;
	case 'lotto_keno':
	    $bets_performance = lotto_keno_betting_system_bets_performance_summary_quick($lottery_name, $apd_numbers, $betting_profile, $set_of_each, $number_of_bets);
	    
	    $header = "<table class=\"betting_system_performance_grid\" ><tbody>";
	    
	    $label1 = "<tr>";
	    $label1 .= "<th>Labels</th>";	    
	    $label1 .= "<th colspan=\"6\" >Diagwin5</th>";
	    $label1 .= "<th></th>";
	    $label1 .= "<th colspan=\"6\" >Diagwin10</th>";
	    $label1 .= "<th></th>";
	    $label1 .= "<th colspan=\"6\" >Diagwin20</th>";
	    $label1 .= "<th></th>";
	    $label1 .= "<th colspan=\"6\" >Diagwin50</th>";
	    $label1 .= "<th></th>";
	    $label1 .= "<th colspan=\"6\" >Diagwin100</th>";
	    $label1 .= "<th></th>";
	    $label1 .= "<th colspan=\"12\" >RatioSum</th>";
	    $label1 .= "</tr>";
	    
	    $label2 = "<tr>";
	    $label2 .= "<th></th>";
	    $label2 .= "<th colspan=\"2\" >Pillar</th>";
	    $label2 .= "<th colspan=\"2\" >Stepup</th>";
	    $label2 .= "<th colspan=\"2\" >Stepdown</th>";
	    $label2 .= "<th></th>";
	    $label2 .= "<th colspan=\"2\" >Pillar</th>";
	    $label2 .= "<th colspan=\"2\" >Stepup</th>";
	    $label2 .= "<th colspan=\"2\" >Stepdown</th>";
	    $label2 .= "<th></th>";
	    $label2 .= "<th colspan=\"2\" >Pillar</th>";
	    $label2 .= "<th colspan=\"2\" >Stepup</th>";
	    $label2 .= "<th colspan=\"2\" >Stepdown</th>";
	    $label2 .= "<th></th>";
	    $label2 .= "<th colspan=\"2\" >Pillar</th>";
	    $label2 .= "<th colspan=\"2\" >Stepup</th>";
	    $label2 .= "<th colspan=\"2\" >Stepdown</th>";
	    $label2 .= "<th></th>";
	    $label2 .= "<th colspan=\"2\" >Pillar</th>";
	    $label2 .= "<th colspan=\"2\" >Stepup</th>";
	    $label2 .= "<th colspan=\"2\" >Stepdown</th>";
	    $label2 .= "<th></th>";
	    $label2 .= "<th colspan=\"2\" >Overall</th>";
	    $label2 .= "<th colspan=\"2\" >Pillar</th>";
	    $label2 .= "<th colspan=\"2\" >Stepup</th>";
	    $label2 .= "<th colspan=\"2\" >Stepdown</th>";
	    $label2 .= "<th></th>";
	    $label2 .= "</tr>";
	    
	    
	    $body = "";
	    $total_spent_html = "<tr><th colspan=\"6\" >Total Spent</th>";
	    $total_won_html = "<tr><th colspan=\"6\" >Total Won</th>";	    
	    $total_profit_html= "<tr><th colspan=\"6\" >Total Profit</th>";
	    
	    foreach($bets_performance as $diagwin_cat=>$data_diag){
		$total_won=0; $total_spent=0; $total_profit=0;
		foreach($data_diag as $cat=>$summary){
		    $total_spent += $summary['bets'];
		    $total_won += array_sum( $summary['win'] );
		}
		$total_profit += $total_won - $total_spent;
		$total_spent_html .= "<th></th><td colspan=\"6\" >".$total_spent."</td>";
		$total_won_html .= "<th></th><td colspan=\"6\" >".$total_won."</td>";    
		$total_profit_html .= "<th></th><td colspan=\"6\" >".$total_profit."</td>";		
	    }
	    
	    //empty overall columns for the moment
	    $total_spent_html .= "<th></th><td colspan=\"8\" >".$total_spent."</td>";
	    $total_won_html .= "<th></th><td colspan=\"8\" >".$total_won."</td>";    
	    $total_profit_html .= "<th></th><td colspan=\"8\" >".$total_profit."</td>";
	    
	    $total_spent_html .= "</tr>";
	    $total_won_html .= "</tr>";  
	    $total_profit_html .= "</tr>";
	   
	    $body .= $total_spent_html . $total_won_html .    $total_profit_html;
	    
	    $footer = "</tbody></table>";
	    
	    $betting_system_performance_grid = $header . $label1 . $label2 . $body. $footer;
	    break;
		
    }
    return $betting_system_performance_grid;
}
?>
