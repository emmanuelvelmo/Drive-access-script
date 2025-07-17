#include <windows.h> // Para las funciones de la API de Windows
#include <tchar.h> // Para manejar caracteres TCHAR (compatibilidad Unicode/ANSI)
#include <stdio.h> // Para funciones de entrada/salida estándar (printf)

// Función principal del programa
int main()
{
    // Obtener un bitmask de las unidades de disco disponibles
    // Cada bit representa una letra de unidad (A-Z), donde 1 = presente, 0 = ausente
    DWORD drives = GetLogicalDrives();

    // Mostrar encabezado
    printf("Unidades de disco disponibles:\n");

    // Recorrer todas las letras posibles de unidades (A-Z)
    for (char letter = 'A'; letter <= 'Z'; ++letter)
    {
        // Verificar si el bit correspondiente a esta letra está activado (1)
        // (1 << (letter - 'A')) desplaza el bit 1 a la posición de la letra actual
        if (drives & (1 << (letter - 'A')))
        {
            // Crear la ruta raíz de la unidad (ej: "C:\")
            TCHAR rootPath[] = { letter, ':', '\\', '\0' };

            // Buffer para almacenar el nombre del volumen (etiqueta del disco)
            TCHAR volumeName[MAX_PATH + 1] = { 0 }; // Inicializado a ceros

            // Obtener información del volumen (disco)
            if (GetVolumeInformation(
                rootPath, // Ruta raíz de la unidad
                volumeName, // Buffer para el nombre del volumen
                MAX_PATH, // Tamaño del buffer
                NULL, // No necesitamos el número de serie
                NULL, // No necesitamos la longitud máxima de nombres
                NULL, // No necesitamos flags del sistema de archivos
                NULL, // No necesitamos el tipo de sistema de archivos
                0))
            { // Flags (0 para ninguno)

                // Si se obtuvo la información, mostrar letra y nombre del volumen
                printf("%c: (%s)\n", letter, volumeName);
            }
            else
            {
                // Si no se pudo obtener información, mostrar solo la letra
                printf("%c: (Sin nombre de volumen)\n", letter);
            }
        }
    }

    // Pausar antes de salir (para que la ventana no se cierre inmediatamente)
    system("pause");

    return 0; // Salir con código de éxito
}