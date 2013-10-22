# Problema de la selección de actividades en programación ávida
class Actividad:
    'Actividades'
    nombre = ''
    horaInicio = -1
    horaFinal = -1

    def __init__(self, horaInicio, horaFinal, nombre):
        self.horaFinal = horaFinal
        self.nombre = nombre
        self.horaInicio = horaInicio
    
    def __str__(self):
        return 'Actividad ' + self.nombre

    def duracion(self):
        return self.horaFinal - self.horaInicio

def burbujaMejorada(array,n):
    for i in range(n):
        for j in range(i):
            if array[i].horaFinal < array[j].horaFinal:
                temp = array[j] 
                array[j] = array[i]
                array[i] = temp

def seleccionarActividades(lista,tamano):
    actividadesSeleccionadas = []
    z = 0
    actividadesSeleccionadas.append(lista[z])
    for i in range(tamano):
        if lista[i].horaInicio >= lista[z].horaFinal:
            actividadesSeleccionadas.append(lista[i])
            z = i        
    return actividadesSeleccionadas
        

numeroActividades = int(input('Numero de actividades: '))
actividades = []
for i in range(numeroActividades):
    horaInicio = int(input('Inicio de la actividad ' + str(i + 1) + ": "))
    horaFinal = int(input('Fin de la actividad ' + str(i + 1) + ": "))
    act = Actividad(horaInicio,horaFinal, 'Actividad ' + str(i + 1))
    actividades.append(act)

burbujaMejorada(actividades,numeroActividades)

seleccionadas = seleccionarActividades(actividades,numeroActividades)

for x in seleccionadas:
    print(x)
