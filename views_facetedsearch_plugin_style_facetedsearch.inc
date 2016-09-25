<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

class views_facetedsearch_plugin_style_facetedsearch extends views_plugin_style {
  function option_definition() {
    $options = parent::option_definition();
    return $options;
  }
  
  function render(){
    drupal_add_js(drupal_get_path('module', 'views_facetedsearch') . '/js/underscore-1.1.7.js');
    drupal_add_js(drupal_get_path('module', 'views_facetedsearch') . '/js/facetedsearch.js');
  
    foreach($this->view->result as $eachValue)
    {
      
    }
    
   
 return theme($this->theme_functions(), array(
    'view' => $this->view,
    'options' => $this->options,
    'rows' => $this->view->result,
//    'mapping' => $this->define_mapping(),
  ));
}

  
  function render_fields($result) {
 // die(print_r($result, TRUE));
}
}