<?php
class Caneca{
    private $id;
    private $longitud;
	private $latitud;
	private $lleno;
	
    public function __GET($k){ return $this->$k; }
    public function __SET($k, $v){ return $this->$k = $v; }
}