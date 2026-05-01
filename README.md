# EngineIconSetter

`EngineIconSetter` is an editor-only Unreal Engine plugin that overrides the editor app icon from a plugin resource.

<img width="171" height="130" alt="Example" src="https://github.com/user-attachments/assets/392d1450-50c6-40bc-9072-06da9ac10eff" />


Current implementation is intentionally simple:
- hardcoded icon path
- hardcoded icon size
- plugin resource based
- no runtime settings UI

## Editor Only

This plugin is editor only.

Module definition:

```json
{
  "Name": "EngineIconSetter",
  "Type": "Editor"
}
```

It is not intended for packaged builds.

## What It Does

On module startup, the plugin:

1. finds its own plugin directory
2. loads an SVG icon from `Resources/Icon.svg`
3. overrides the `AppIcon` brush in `FAppStyle`

On module shutdown, it restores the previous icon brush.

## Current Hardcoded Setup

Current source:

- [EngineIconSetter.cpp](C:\Users\Wellsaik\source\repos\abberation\Plugins\EngineIconSetter\Source\EngineIconSetter\Private\EngineIconSetter.cpp)

Current hardcoded values:

- icon path:

```text
Resources/Icon.svg
```

- icon size:

```cpp
FVector2D(48.0f, 48.0f)
```

## SVG Icons

This plugin uses SVG icons.

Why:
- clean scaling
- easy replacement
- good fit for Slate vector brushes

Expected file:

```text
Plugins/EngineIconSetter/Resources/Icon.svg
```

## Installation

Copy the plugin into your project:

```text
<YourProject>/Plugins/EngineIconSetter
```

Folder example:

```text
YourProject/
├─ Plugins/
│  └─ EngineIconSetter/
│     ├─ Resources/
│     │  └─ Icon.svg
│     ├─ Source/
│     └─ EngineIconSetter.uplugin
└─ YourProject.uproject
```

Then:

1. regenerate project files if needed
2. build the project
3. make sure the plugin is enabled in the project
4. restart the editor

## Add Plugin To `.uproject`

You should also enable the plugin in your `.uproject`.

Example:

```json
{
  "Plugins": [
    {
      "Name": "EngineIconSetter",
      "Enabled": true
    }
  ]
}
```

If your project already has a `Plugins` array, just add the new entry.

## How To Change The Icon

Replace:

```text
Plugins/EngineIconSetter/Resources/Icon.svg
```

with your own SVG file.

Keep the same filename if you do not want to change code.

After replacing the file:

1. rebuild if needed
2. restart the editor

## How To Change Icon Size

Icon size is hardcoded in:

- [EngineIconSetter.cpp](C:\Users\Wellsaik\source\repos\abberation\Plugins\EngineIconSetter\Source\EngineIconSetter\Private\EngineIconSetter.cpp)

Current line concept:

```cpp
new FSlateVectorImageBrush(iconPath, FVector2D(48.0f, 48.0f))
```

Change the `FVector2D` values to whatever you need.

Then rebuild and restart the editor.

## Notes

- plugin path is resolved through `IPluginManager`
- the icon is loaded from the plugin `Resources` folder
- this implementation currently expects a local plugin resource, not a project setting
- changing the icon usually requires editor restart

## Repository Structure

```text
EngineIconSetter/
├─ Resources/
│  └─ Icon.svg
├─ Source/
│  └─ EngineIconSetter/
│     ├─ Public/
│     └─ Private/
├─ EngineIconSetter.uplugin
└─ README.md
```

## Extending The Plugin

The current version is minimal on purpose.

Possible next step:

### Developer Settings Support

You can implement custom icon selection through `UDeveloperSettings`.

That would allow:
- choosing icon path in `Project Settings -> Plugins`
- storing a project-relative path
- exposing icon size in settings
- adding restart notice in editor UI

Recommended settings fields:
- `bool bOverrideAppIcon`
- `FFilePath IconFile`
- `FVector2D IconSize`

Recommended behavior:
- let users pick an SVG file
- convert absolute picked path to project-relative when possible
- resolve path against `ProjectDir` at startup

If you want this workflow, make your own fork and add a settings object.

## Troubleshooting

### Icon does not change

Check:
- plugin is enabled in `.uproject`
- `Resources/Icon.svg` exists
- the editor was restarted
- build succeeded

### Plugin loads but icon is still default

Possible reasons:
- module loading is too late
- editor window icon was already initialized
- the current engine version does not refresh native window icon from this style override path

### Wrong file format

Current implementation is written for SVG:

```cpp
FSlateVectorImageBrush
```

If you want PNG support, code changes are needed.

## License

Project is licensed under [MIT](LICENSE)

