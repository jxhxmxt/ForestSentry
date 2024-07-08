package com.forestsentry.SentryAPI.controllers;

import java.util.UUID;
import java.util.List;
import java.util.ArrayList;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Page;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import com.forestsentry.SentryAPI.models.dtos.RecordDTO;
import com.forestsentry.SentryAPI.models.dtos.request.RecordGroupRequestDTO;
import com.forestsentry.SentryAPI.models.dtos.response.PageResponseDTO;
import com.forestsentry.SentryAPI.models.entities.Record;
import com.forestsentry.SentryAPI.services.dec.RecordService;

import jakarta.validation.Valid;

@RestController
@RequestMapping("/API")
@CrossOrigin("*")
public class MainController {
    
    @Autowired
    private RecordService recordService;

    @PostMapping(path = "/Data/Post", consumes = "application/json")
    public ResponseEntity<?> saveRecord(@RequestBody @Valid RecordDTO dto, BindingResult result){
        try{
            if(result.hasErrors()){
                return new ResponseEntity<>(result.getAllErrors(), HttpStatus.BAD_REQUEST);
            }
            if(recordService.save(dto)){
                return new ResponseEntity<>(HttpStatus.OK);
            }
            else{
                return new ResponseEntity<>(HttpStatus.INTERNAL_SERVER_ERROR);
            }
        }
        catch(Exception e){
            e.printStackTrace();
            System.out.println(e.getMessage());
            return new ResponseEntity<>(HttpStatus.INTERNAL_SERVER_ERROR);
        }
    }

    @GetMapping("/Latest")
    public ResponseEntity<?> getLatestRecord(){
        try{
            Record r = recordService.findLatest();
            RecordDTO body = new RecordDTO(r);
            return new ResponseEntity<>(body, HttpStatus.OK);
        }
        catch(Exception e){
            e.printStackTrace();
            System.out.println(e.getMessage());
            return new ResponseEntity<>(HttpStatus.INTERNAL_SERVER_ERROR);
        }
    }

    @GetMapping("/ID/{id}")
    public ResponseEntity<?> getRecordById(@PathVariable(name = "id") UUID id){
        try{
            Record r = recordService.findById(id);
            RecordDTO body = new RecordDTO(r);
            return new ResponseEntity<>(body, HttpStatus.OK);
        }
        catch(Exception e){
            e.printStackTrace();
            System.out.println(e.getMessage());
            return new ResponseEntity<>(HttpStatus.INTERNAL_SERVER_ERROR);
        }
    }

    @GetMapping("/Latest/{id}")
    public ResponseEntity<?> getAllRecordsById(@PathVariable(name = "id") String id, @RequestParam(name = "page", defaultValue = "0") Integer page, @RequestParam(name = "size", defaultValue = "10") Integer size){
        try{
            Page<Record> rawRecords = recordService.findByDeviceId(id, page, size);
            List<RecordDTO> content = new ArrayList<>();
            rawRecords.forEach(r -> {
                content.add(new RecordDTO(r));
            });
            PageResponseDTO<RecordDTO> body = new PageResponseDTO<>(content, rawRecords.getTotalPages(), rawRecords.getTotalElements());
            return new ResponseEntity<>(body, HttpStatus.FOUND);
        }
        catch(Exception e){
            e.printStackTrace();
            System.out.println(e.getMessage());
            return new ResponseEntity<>(HttpStatus.INTERNAL_SERVER_ERROR);
        }
    }

    @PostMapping("/Latest/Group")
    public ResponseEntity<?> getLatestRecordsForGroup(@ModelAttribute @Valid RecordGroupRequestDTO dto, BindingResult result){
        try{
            if(result.hasErrors()){
                return new ResponseEntity<>(result.getAllErrors(), HttpStatus.BAD_REQUEST);
            }
            List<Record> rawRecords = recordService.findLatestByDeviceId(dto.getIdList());
            List<RecordDTO> content = new ArrayList<>();
            rawRecords.forEach(r -> {
                content.add(new RecordDTO(r));
            });
            return new ResponseEntity<>(content, HttpStatus.OK);
        }
        catch(Exception e){
            e.printStackTrace();
            System.out.println(e.getMessage());
            return new ResponseEntity<>(HttpStatus.INTERNAL_SERVER_ERROR);
        }
    }
}