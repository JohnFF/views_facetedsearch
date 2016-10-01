<?php

/**
 * Create the variables used by the theme.
 * @param type $vars
 */
function  _views_facetedsearch_preprocess_views_facetedsearch(&$vars) {
  $vars['views_facetedsearch_facets'] = _views_facetedsearch_get_facets($vars['view'],
      'views_facetedsearch_facets_');
  $vars['views_facetedsearch_facetorders'] = _views_facetedsearch_get_facets($vars['view'],
      'views_facetedsearch_facetorders_');
  $vars['views_facetedsearch_itemtemplate'] = str_replace(array("\r", "\n"),
      '', $vars['view']->style_options['views_facetedsearch_itemtemplate']);
  $vars['views_facetedsearch_resultscontainer'] = str_replace(array("\r", "\n"),
      '', $vars['view']->style_options['views_facetedsearch_resultscontainer']);
  $vars['views_facetedsearch_resultsheader'] = str_replace(array("\r", "\n"),
      '', $vars['view']->style_options['views_facetedsearch_resultsheader']);
  $vars['views_facetedsearch_facetcontainer'] = str_replace(array("\r", "\n"),
      '', $vars['view']->style_options['views_facetedsearch_facetcontainer']);
  $vars['views_facetedsearch_facetlistcontainer'] = str_replace(array("\r", "\n"),
      '', $vars['view']->style_options['views_facetedsearch_facetlistcontainer']);
  
  $vars['views_facetedsearch_results'] = _views_facetedsearch_get_results($vars['view']);
}

/**
 * Create an individual variable used by the theme.
 *
 * @param Object $view
 * @param string $option_start
 * @return string
 */
function _views_facetedsearch_get_facets($view, $option_start) {
  $options_array = array();
  foreach ($view->display['default']->handler->options['fields'] as $key => $facet) {
    if (!array_key_exists($option_start . $key, $view->style_options)) {
      watchdog('views_facetedsearch', 'Could not find %1 in list of options',
          array('%1' => $option_start . $key), WATCHDOG_ERROR);
      continue;
    }

    if ($view->style_options[$option_start . $key] === 0) {
      continue;
    }

    if (array_key_exists('label', $view->display['default']->handler->options['fields'][$key])) {
      $label = $view->display['default']->handler->options['fields'][$key]['label'];
    }
    else {
      $label = $facet;
    }
    $options_array[] = "'$key' : '$label'";
  }
  $facet_options_string = implode(', ', $options_array);
  return $facet_options_string;
}

/**
 * Translates the view data into a format that can be interpreted.
 * 
 * @param Object $view
 * @return string $output - the view data in the format faceted search can interpret.
 */
function _views_facetedsearch_get_results($view){
    $output = '';
    
    // Populate the results items from the views data.
    $resultCount = count($view->result);
    $resultIndex = 0;

    if (count($view->style_plugin->rendered_fields) > 0){
      $attributeCount = count((array) $view->style_plugin->rendered_fields[0]);
    }

    foreach ($view->style_plugin->rendered_fields  as $resultIndex => $eachResult) {
      $eachResult = (array) $eachResult; // Cast each object into an array.
      $attributeIndex = 0;
      $output .= '{';
      foreach ($eachResult as $attributeKey => $attribute){
        $output .= '"' . addslashes($attributeKey) . '" : "' . addslashes(str_replace(array("\r", "\n"), '', $attribute)) . '"';
        $attributeIndex++;
        if ($attributeIndex != $attributeCount){
          $output .= ",\n";
        }
      }
      $output .= '}';
      $resultIndex ++;
      if ($resultIndex != $resultCount){
        $output .= ",\n";
      }
    }
  return $output;  
}
