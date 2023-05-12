# Left4Dead

## Testing

Para correr tests, incluir el argumento `-DTESTING=ON` al invocar cmake. Ejemplo: `cmake -DTESTING=ON <PROJECT_ROOT_DIRECTORY> -B <BUILD_DIRECTORY>`

Luego correr `cmake --build <BUILD_DIRECTORY> --target test`

Ver README en **`test/`** para más info.