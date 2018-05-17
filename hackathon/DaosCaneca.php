<?php
require_once 'CRUD.php';
require_once 'Caneca.php';

class DaosCaneca extends CRUD
{
    public function __CONSTRUCT($user,$password)
    {
        parent::__construct($user,$password);
    }

    public function Listar()
    {
        try
        {
            $result = array();

            $stm = $this->pdo->prepare("SELECT * FROM bote");
            $stm->execute();

            foreach($stm->fetchAll(PDO::FETCH_OBJ) as $r)
            {
                $canecAc = new Caneca();

                $canecAc->__SET('id', $r->id);
                $canecAc->__SET('latitud', $r->latitud);
				$canecAc->__SET('longitud', $r->longitud);
                $canecAc->__SET('lleno', $r->lleno);
				
                $result[] = $canecAc;
            }

            return $result;
        }
        catch(Exception $e)
        {
            die($e->getMessage());
        }
    }

	//READ
    public function Obtener($id)
    {
        try 
        {
            $stm = $this->pdo
                      ->prepare("SELECT * FROM bote WHERE id = ?");
                      
            $stm->execute(array($id));
            $r = $stm->fetch(PDO::FETCH_OBJ);

            $canecAc = null;
			if(strlen($r)<=0){
				
			}else{
            $canecAc = new Caneca();
			$canecAc->__SET('id', $r->id);
            $canecAc->__SET('latitud', $r->latitud);
			$canecAc->__SET('longitud', $r->longitud);
            $canecAc->__SET('lleno', $r->lleno);
			}
            return $canecAc;
        } catch (Exception $e) 
        {
            die($e->getMessage());
        }
    }

	//DELETE
    public function Eliminar($id)
    {
        try 
        {
            $stm = $this->pdo
                      ->prepare("DELETE FROM bote WHERE id = ?");                      

            $stm->execute(array($id));
        } catch (Exception $e) 
        {
            die($e->getMessage());
        }
    }

	//UPDATE
    public function Actualizar(Caneca $data)
    {
        try 
        {
            $sql = "UPDATE bote SET 
                        lleno        = ?
                    WHERE id = ?";

            $this->pdo->prepare($sql)
                 ->execute(
                array(
                    $data->__GET('lleno'),
                    $data->__GET('id')
                    )
                );
        } catch (Exception $e) 
        {
            die($e->getMessage());
        }
    }

	//CREATE
    public function Registrar(Caneca $data)
    {
        try 
        {
        $sql = "INSERT INTO bote (latitud,longitud,lleno) 
                VALUES (?, ?, ?)";

        $this->pdo->prepare($sql)
             ->execute(
            array(
                $data->__GET('latitud'), 
                $data->__GET('longitud'),
				$data->__GET('lleno')
                )
            );
        } catch (Exception $e) 
        {
            die($e->getMessage());
        }
    }
}