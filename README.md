# swc2pvecf
Specifies service for conversion of swc file to pvec with following methods

## /clearpvecs
Clear previously submitted files

## /sendfile [POST]
Requires swc file as POST payload

## /calcpvecs
Will calculate sent pvecs

## /getjson
Fetch calculated pvecs as JSON with following structure for each neuron with name *neuronname*
```json
{"pvecs": 
  {"[neuronname]": 
    {
            "distance": "[calculated distance]",
            "Sfactor": "[calculated scaling factor]",
            "vector": "[calculated coeff vector"]
    }
  }
}
```
## /download-zip
Zips calculated pvecs and returns as zip file


