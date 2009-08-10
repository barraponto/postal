<?php // $Id$

function postal_admin_load_countries($countries = NULL) {
  $ret = drupal_http_request('http://download.geonames.org/export/dump/countryInfo.txt');
  foreach (explode("\n", $ret->data) as $row) {
    if ($row[0] == '#') continue;  // Skip comments.

    $c = explode("\t", $row);
    $item = array(
      'id' => $c[16],
      'parent_id' => NULL,
      'status' => 1, // TODO retain this
      'weight' => 0, // TODO retain this
      'iso' => $c[0],
      'iso3' => $c[1],
      'ison' => $c[2],
      'fips' => $c[3],
      'name' => $c[4],
      'zip_format' => $c[13],
      'zip_regex' => $c[14],
      'children' => NULL,
    );
    if ($item['name']) drupal_write_record('postal', $item);
  }
}
