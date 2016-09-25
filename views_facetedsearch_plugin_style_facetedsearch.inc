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
  
  // Build the settings form for the view.
  function options_form(&$form, &$form_state) {

    parent::options_form($form, $form_state);
    
    $selectedFields = $form_state['view']->display_handler->display->handler->view->
        display['default']->handler->view->display_handler->default_display->display->
        display_options['fields'];
    
    foreach($selectedFields as $selectedFieldKey => $eachSelectedField){
      $optionKey = 'views_facetedsearch_facets_' . $eachSelectedField['table'] . '_' . $eachSelectedField['field'] ;
      if (array_key_exists('label', $eachSelectedField)){
        $optionTitle = t($eachSelectedField['label']);
      }
      else {
        $optionTitle = t($eachSelectedField['id']);
      }
      
      $form[$optionKey] = array(
        '#type' => 'checkbox',
        '#title' => t($optionTitle),
        //'#options' => $facetOptions,
        '#default_value' => $this->options[$optionKey],
        '#description' => t('Check box to display allow searching by facet.'),
      );
    }

    // Create the drop down box so users can choose an available skin.

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