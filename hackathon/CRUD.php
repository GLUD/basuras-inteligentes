<?php
abstract class CRUD{
	protected $pdo;

    public function __CONSTRUCT($user,$password)
    {
        try
        {
            $this->pdo = new PDO('mysql:host=localhost;dbname=hackathon', $user, $password);
            $this->pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);                
        }
        catch(Exception $e)
        {
            die($e->getMessage());
        }
    }

    abstract public function Listar();
	//READ
    abstract public function Obtener($nombre);
	//DELETE
    abstract public function Eliminar($nombre);
}