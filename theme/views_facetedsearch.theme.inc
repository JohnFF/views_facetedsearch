<?php

/**
 * Create the variables used by the theme.
 * @param type $vars
 */
function  _views_facetedsearch_preprocess_views_facetedsearch(&$vars) {
  $vars['views_facetedsearch_facets'] = _views_facetedsearch_get_facets($vars['view'], 'views_facetedsearch_facets_');
  $vars['views_facetedsearch_facetorders'] = _views_facetedsearch_get_facets($vars['view'], 'views_facetedsearch_facetorders_');
  $vars['views_facetedsearch_itemtemplate'] = str_replace(array("\r", "\n"), '', $vars['view']->style_options['views_facetedsearch_itemtemplate']);
  $vars['views_facetedsearch_resultscontainer'] = str_replace(array("\r", "\n"), '', $vars['view']->style_options['views_facetedsearch_resultscontainer']);
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
      watchdog('views_facetedsearch', 'Could not find %1 in list of options', array('%1' => $option_start . $key), WATCHDOG_ERROR);
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