const BASE_URL_API = "https://eloquent-determination-production.up.railway.app" /* La URL Base para no repetirla siempre */

const API = {}; /* nuestro arreglo de funciones poder llamarlas */


API.GetLatest = async() => { /* Obtener todos con sus Props Limit y page, para poder luego hacer el InfiniteScroll */
    try {
        const Response = await fetch(`${BASE_URL_API}/API/Latest`, {
            method: "GET",
        })
        const d = await Response.json()
        console.log(d)
        return d

    } catch (error) {
        console.log(error)
    }
}

API.GetByUuid = async(uuid) => { /* Obtener todos con sus Props Limit y page, para poder luego hacer el InfiniteScroll */
    try {
        const Response = await fetch(`${BASE_URL_API}/API/${uuid}`, {
            method: "GET",
            headers: {
                'Content-Type': 'application/json'
            },
        })
        const data = await Response.json()
        return data
    } catch (error) {
        console.log(error)
    }
}

API.GetByGroup = async(DeviceId, page, size) => { /* Obtener todos con sus Props Limit y page, para poder luego hacer el InfiniteScroll */
    try {
        const Response = await fetch(`${BASE_URL_API}/API/Latest/${DeviceId}?page=${page}&size=${size}`, {
            method: "GET"
        })
        const data = await Response.json()
        return data
    } catch (error) {
        console.log(error)
    }
}


export default API; /* Exportando servicios  */